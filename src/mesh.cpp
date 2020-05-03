#include "mesh.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <GL/glew.h>
#include "logger.h"
#include "texture.h"

Mesh::Mesh(const std::string& object_file_name, glm::vec3 position, glm::vec3 scale)
        : m_position(position), m_scale(scale) {

    std::cout << "Loading mesh : " << object_file_name << std::endl;

    Assimp::Importer importer;

    // Unitize object in size (scale the model to fit into (-1..1)^3)
//    importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

    // Load asset from the file - you can play with various processing steps
    const aiScene* scene = importer.ReadFile(
            object_file_name.c_str(), 0
                                      // Triangulate polygons (if any).
                                      | aiProcess_Triangulate
                                      // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
                                      | aiProcess_PreTransformVertices
                                      // Calculate normals per vertex.
                                      | aiProcess_GenSmoothNormals
                                      | aiProcess_JoinIdenticalVertices);

    // abort if the loader fails
    if (scene == nullptr) {
        std::cerr << "assimp error: " << importer.GetErrorString() << std::endl;
        throw std::exception();
    }

    // some formats store whole scene (multiple meshes and materials, lights, cameras, ...) in one file, we cannot handle that in our simplified example
    if (scene->mNumMeshes != 1) {
        std::cerr << "this simplified loader can only process files with only one mesh" << std::endl;
//        throw std::exception();
    }

    // in this phase we know we have one mesh in our loaded scene, we can directly copy its data to OpenGL ...
    const aiMesh* mesh = scene->mMeshes[0];

    // just texture 0 for now
    auto* tex_coords = new float[2 * mesh->mNumVertices];  // 2 floats per vertex
    float* cur_tex_coord = tex_coords;

    // copy texture coordinates
    aiVector3D vect;

    if (mesh->HasTextureCoords(0)) {
        // we use 2D textures with 2 coordinates and ignore the third coordinate
        for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) {
            vect = (mesh->mTextureCoords[0])[idx];
            *cur_tex_coord++ = vect.x;
            *cur_tex_coord++ = vect.y;
        }
    }

    float min_x = std::numeric_limits<float>::infinity();
    float min_y = std::numeric_limits<float>::infinity();
    float min_z = std::numeric_limits<float>::infinity();

    float max_x = -std::numeric_limits<float>::infinity();
    float max_y = -std::numeric_limits<float>::infinity();
    float max_z = -std::numeric_limits<float>::infinity();

    for (unsigned int f = 0; f < mesh->mNumVertices; f++) {
        if (mesh->mVertices[f].x > max_x)
            max_x = mesh->mVertices[f].x;
        if (mesh->mVertices[f].y > max_y)
            max_y = mesh->mVertices[f].y;
        if (mesh->mVertices[f].z > max_z)
            max_z = mesh->mVertices[f].z;

        if (mesh->mVertices[f].x < min_x)
            min_x = mesh->mVertices[f].x;
        if (mesh->mVertices[f].y < min_y)
            min_y = mesh->mVertices[f].y;
        if (mesh->mVertices[f].z < min_z)
            min_z = mesh->mVertices[f].z;
    }

    m_pivot = glm::vec3(min_x + (max_x - min_x) / 2, min_y + (max_y - min_y) / 2, min_z + (max_z - min_z) / 2);

    // allocate memory for vertices, normals, and texture coordinates
    vbo = std::shared_ptr<VertexBuffer>::make_shared(*new VertexBuffer(sizeof(float) * mesh->mNumVertices, 8));
    // load vertices to GPU
    vbo->Push(mesh->mVertices, 3);
    // load normals to GPU
    vbo->Push(mesh->mNormals, 3);
    // load texture coordinates to GPU
    vbo->Push(tex_coords, 2);

//    if (strcmp(scene->mRootNode->mName.data, "island_bridge.obj") == 0) {
//        for (unsigned int f = 0; f < mesh->mNumVertices; f++) {
//            std::cout
//                    << mesh->mVertices[f].x << ", " << mesh->mVertices[f].y << ", " << mesh->mVertices[f].z << ", "
//                    << mesh->mNormals[f].x << ", " << mesh->mNormals[f].y << ", " << mesh->mNormals[f].z << ", "
//                    << tex_coords[f * 2] << ", " << tex_coords[f * 2 + 1] << ", "
//                    << std::endl;
//        }
//    }



    // copy all mesh faces into one big array (assimp supports faces with ordinary number of vertices, we use only 3 -> triangles)
    auto* indices = new unsigned int[mesh->mNumFaces * 3];

    for (unsigned int f = 0; f < mesh->mNumFaces; f++) {
        indices[f * 3 + 0] = mesh->mFaces[f].mIndices[0];
        indices[f * 3 + 1] = mesh->mFaces[f].mIndices[1];
        indices[f * 3 + 2] = mesh->mFaces[f].mIndices[2];

//        if (strcmp(scene->mRootNode->mName.data, "island_bridge.obj") == 0) {
//            std::cout << mesh->mFaces[f].mIndices[0] << ", "
//                      << mesh->mFaces[f].mIndices[1] << ", "
//                      << mesh->mFaces[f].mIndices[2] << ", "
//                      << std::endl;
//        }
    }

    // copy our temporary index array to OpenGL and free the array
    ibo = std::shared_ptr<IndexBuffer>::make_shared(*new IndexBuffer(indices, 3 * mesh->mNumFaces));

    delete[] indices;

    // copy the material info to MeshGeometry structure
    const aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
    aiColor4D color;
    aiString name;
    aiReturn retValue = AI_SUCCESS;

    // get returns: aiReturn_SUCCESS 0 | aiReturn_FAILURE -1 | aiReturn_OUTOFMEMORY -3
    mat->Get(AI_MATKEY_NAME, name); // may be "" after the input mesh processing. Must be aiString type!

    if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS)
        color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);

    m_diffuse = glm::vec3(color.r, color.g, color.b);

    if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS)
        color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
    m_ambient = glm::vec3(color.r, color.g, color.b);

    if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS)
        color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
    m_specular = glm::vec3(color.r, color.g, color.b);

    ai_real shininess, strength;
    unsigned int max;

    max = 1;
    if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS, &shininess, &max)) != AI_SUCCESS)
        shininess = 1.0f;
    max = 1;
    if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS_STRENGTH, &strength, &max)) != AI_SUCCESS)
        strength = 1.0f;
    m_shininess = shininess * strength;

    // load texture image
    if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        // get texture name
        aiString path; // filename

        mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        std::string tex_name = path.data;
        std::cout << "Loading texture : " << tex_name << std::endl;
        m_texture = std::shared_ptr<Texture>::make_shared(*new Texture("res/textures/" + tex_name));

//        size_t found = object_file_name.find_last_of("/\\");
        // insert correct texture file path
//        if (found != std::string::npos) { // not found
        //subMesh_p->tex_name.insert(0, "/");
//            tex_name.insert(0, object_file_name.substr(0, found + 1));
//        }


//        std::cerr << "Textures are not supported yet" << std::endl;

    }

    // Create layout for this mesh
    layout = std::shared_ptr<BufferLayout>::make_shared(*new BufferLayout());
    // Push layout for 3 coordinates for position
    layout->Push(GL_FLOAT, 3, GL_FALSE, 0);
    // Push layout for 3 coordinates for normals
    layout->Push(GL_FLOAT, 3, GL_FALSE, 0);
    // Push layout for 2 texture coordinates
    layout->Push(GL_FLOAT, 2, GL_FALSE, 0);

    vao = std::shared_ptr<VertexArray>::make_shared(*new VertexArray());
    vao->AddBuffer(*vbo, *layout, mesh->mNumVertices);

}