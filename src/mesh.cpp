#include "mesh.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <GL/glew.h>
#include "logger.h"

Mesh::Mesh(const std::string& object_file_name, Shader& shader) {
    Assimp::Importer importer;

    // Unitize object in size (scale the model to fit into (-1..1)^3)
    importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

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
        throw std::exception();
    }

    // in this phase we know we have one mesh in our loaded scene, we can directly copy its data to OpenGL ...
    const aiMesh* mesh = scene->mMeshes[0];

    // just texture 0 for now
    auto* textureCoords = new float[2 * mesh->mNumVertices];  // 2 floats per vertex
    float* currentTextureCoord = textureCoords;

    // copy texture coordinates
    aiVector3D vect;

    if (mesh->HasTextureCoords(0)) {
        // we use 2D textures with 2 coordinates and ignore the third coordinate
        for (unsigned int idx = 0; idx < mesh->mNumVertices; idx++) {
            vect = (mesh->mTextureCoords[0])[idx];
            *currentTextureCoord++ = vect.x;
            *currentTextureCoord++ = vect.y;
        }
    }

    // allocate memory for vertices, normals, and texture coordinates
    vbo = std::shared_ptr<VertexBuffer>::make_shared(*new VertexBuffer(sizeof(float) * mesh->mNumVertices, 8));
    // load vertices to GPU
    vbo->Push(mesh->mVertices, 3);
    // load normals to GPU
    vbo->Push(mesh->mNormals, 3);
    // load texture coordinates to GPU
    vbo->Push(textureCoords, 2);



    // copy all mesh faces into one big array (assimp supports faces with ordinary number of vertices, we use only 3 -> triangles)
    auto* indices = new unsigned int[mesh->mNumFaces * 3];

    for (unsigned int f = 0; f < mesh->mNumFaces; ++f) {
        indices[f * 3 + 0] = mesh->mFaces[f].mIndices[0];
        indices[f * 3 + 1] = mesh->mFaces[f].mIndices[1];
        indices[f * 3 + 2] = mesh->mFaces[f].mIndices[2];
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

        aiReturn texFound = mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
        std::string textureName = path.data;

        size_t found = object_file_name.find_last_of("/\\");
        // insert correct texture file path
        if (found != std::string::npos) { // not found
            //subMesh_p->textureName.insert(0, "/");
            textureName.insert(0, object_file_name.substr(0, found + 1));
        }

        std::cout << "Loading texture file: " << textureName << std::endl;
//        (*geometry)->texture = pgr::createTexture(textureName);
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