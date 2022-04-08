#include "Headers.h"

class Transformation
{
    public:
        Transformation();
        ~Transformation();
        glm::mat4 GetRotationMatrix(float rotationAngle);
        glm::mat4 GetTranslationMatrix(glm::vec3 translation);
};