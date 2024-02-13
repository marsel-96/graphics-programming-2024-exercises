#include <ituGL/core/BufferObject.h>

// Create the object initially null, get object handle and generate 1 buffer
BufferObject::BufferObject() : Object(NullHandle)
{
    Handle& handle = GetHandle();
    glGenBuffers(1, &handle);
}

// Get object handle and delete 1 buffer
BufferObject::~BufferObject()
{
    Handle& handle = GetHandle();
    glDeleteBuffers(1, &handle);
}

// Bind the buffer handle to the specific target
void BufferObject::Bind(Target target) const
{
    Handle handle = GetHandle();
    switch(target)
    {
        case Target::ArrayBuffer:
            glBindBuffer(GL_ARRAY_BUFFER, handle);
            break;
        case Target::ElementArrayBuffer:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
            break;
        default:
            break;
    }
}

// Bind the null handle to the specific target
void BufferObject::Unbind(Target target)
{
    switch(target)
    {
        case Target::ArrayBuffer:
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            break;
        case Target::ElementArrayBuffer:
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            break;
        default:
            break;
    }
}

// Get buffer Target and allocate buffer data
void BufferObject::AllocateData(size_t size, Usage usage)
{
    auto target = GetTarget();
    switch (usage) {
        case Usage::StaticDraw:
            glBufferData(target, (GLint) size, nullptr, GL_STATIC_DRAW);
            break;
    }
}

// Get buffer Target and allocate buffer data
void BufferObject::AllocateData(std::span<const std::byte> data, Usage usage)
{
    auto target = GetTarget();
    switch (usage) {
        case Usage::StaticDraw:
            glBufferData(target, (GLint) data.size(), data.data(), GL_STATIC_DRAW);
            break;
    }
}

// Get buffer Target and set buffer subdata
void BufferObject::UpdateData(std::span<const std::byte> data, size_t offset)
{
    auto target = GetTarget();
    glBufferSubData(target, (GLint) offset, (GLint) data.size_bytes(), data.data());
}
