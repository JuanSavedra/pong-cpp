#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer {
public:
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

    void drawSprite(glm::vec2 position, glm::vec2 size, glm::vec4 color = glm::vec4(1.0f));
private:
    Shader shader;
    unsigned int quadVAO;
    void initRenderData();
};

#endif