#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class GLCamera {
    public:
        GLCamera();
        GLCamera(const glm::vec3& position, const glm::vec3& viewDirection, const glm::vec3& U, const glm::vec3& V, const glm::vec3& W){
            pos = position;
            viewDir = viewDirection;
            this->U = U;
            this->V = V;
            this->W = W;
        };
        void setPosition(const glm::vec3& position) { pos = position; }
        void setViewDirection(const glm::vec3& viewDirection) { viewDir = viewDirection; }
        void setCameraBasis(const glm::vec3& U, const glm::vec3& V, const glm::vec3& W) {
            this->U = U;
            this->V = V;
            this->W = W;
        }
        glm::vec3 getPosition() const { return pos; }
        glm::vec3 getViewDirection() const { return viewDir; }
        glm::vec3 getU() const { return U; }
        glm::vec3 getV() const { return V; }
        glm::vec3 getW() const { return W; }

    private:
        glm::vec3 pos;
        glm::vec3 viewDir;
        glm::vec3 U, V, W;
};