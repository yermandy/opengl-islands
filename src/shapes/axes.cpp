#include "axes.h"


Axes::Axes() {

    const float axes_data[] = {
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // center (X)
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // axis X

            0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // center Y
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // axis Y

            0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // center Z
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // axis Z
    };

    const unsigned int axes_indices[] = {
            0, 1,
            2, 3,
            4, 5
    };

    vbo = std::shared_ptr<VertexBuffer>::make_shared(*new VertexBuffer(axes_data, sizeof(axes_data)));

    layout = std::shared_ptr<BufferLayout>::make_shared(*new BufferLayout());
    layout->Push(GL_FLOAT, 3, GL_FALSE);
    layout->Push(GL_FLOAT, 3, GL_FALSE);

    vao = std::shared_ptr<VertexArray>::make_shared(*new VertexArray());
    vao->AddBuffer(*vbo, *layout);

    ibo = std::shared_ptr<IndexBuffer>::make_shared(*new IndexBuffer(axes_indices, sizeof(axes_indices)));
}

Axes::~Axes() = default;
