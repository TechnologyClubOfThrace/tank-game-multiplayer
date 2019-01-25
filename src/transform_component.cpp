#include "transform_component.h"

TransformComponent::TransformComponent()
{

}

//copy constructor
TransformComponent::TransformComponent(const TransformComponent &other)
{
    this->Position = other.Position;
    this->RotationAngleDegrees = other.RotationAngleDegrees;
    this->Scale = other.Scale;
}

TransformComponent &TransformComponent::operator=(TransformComponent rhs)
{
    this->Position = rhs.Position;
    this->RotationAngleDegrees = rhs.RotationAngleDegrees;
    this->Scale = rhs.Scale;
    return *this;
}
