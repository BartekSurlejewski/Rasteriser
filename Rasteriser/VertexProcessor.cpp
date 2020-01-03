#include "pch.h"
#include "VertexProcessor.h"
#include "math.h"


VertexProcessor::VertexProcessor()
{
}

void VertexProcessor::setPerspective(float& fovY, const float& aspect, const float& near, const float& far)
{
	fovY *= 0.0087263f;
	float f = cos(fovY) / sin(fovY);
	projectionMatrix = Matrix4x4f(f / aspect, 0, 0, 0,
		0, f, 0, 0,
		0, 0, (far + near) / (near - far), -1,
		0, 0, 2 * far * near / (near - far), 0);
}

void VertexProcessor::setLookAt(const Vector3f& eye, const Vector3f& center, Vector3f& up)
{
	Vector3f f = center + -eye;
	f = f.normalized();
	up = up.normalized();
	Vector3f s = f.crossProduct(up);
	Vector3f u = s.crossProduct(f);

	viewMatrix = Matrix4x4f(s.x, u.x, -f.x, 0,
		s.y, u.y, -f.y, 0,
		s.z, u.z, -f.z, 0,
		-eye.x, -eye.y, -eye.z, 1);
}
