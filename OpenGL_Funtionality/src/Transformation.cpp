#include "Transformation.h"

Transformation::Transformation()
{

}

Transformation :: ~ Transformation()
{

}

glm::mat4 Transformation :: GetRotationMatrix(float rotationAngle)
{
    // Initialize matrix to identity matrix first
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(rotationAngle), glm::vec3(0.0, 0.0, 1.0));
    return trans;
}

glm::mat4 Transformation :: GetTranslationMatrix(glm::vec3 translation)
{
    glm::mat4 identityMatrix  = glm::mat4(1.0f);
    return glm::translate(identityMatrix, translation);
}