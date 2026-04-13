#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class GLCamera {
    public:
        GLCamera();
        float pitch = 0.0f;
        float yaw = -90.0f;
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

        void updateFromAngles(){
            glm::vec3 front;
            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

            viewDir = glm::normalize(front);

            glm::vec3 up(0.0f, 1.0f, 0.0f);

            W = -viewDir;
            U = glm::normalize(glm::cross(viewDir, up));   // 🔥 FIX HERE
            V = glm::cross(U, viewDir);
        }

    private:
        glm::vec3 pos;
        glm::vec3 viewDir;
        glm::vec3 U, V, W;
};