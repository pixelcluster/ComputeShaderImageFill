#version 430 core

const vec3[] verts = {
		vec3(-1.0f,  1.0f, 0.0f),
		vec3(-1.0f, -1.0f, 0.0f),
		vec3(1.0f, -1.0f, 0.0f),
		vec3(1.0f,  1.0f, 0.0f) };
const vec2[] uvs = {
		vec2(0.0f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f)
};
const uint[] indices = {
			2, 3, 0,
			0, 1, 2
};

out vec2 texcoord;

void main() {
	texcoord = uvs[indices[gl_VertexID]];
	gl_Position = vec4(verts[indices[gl_VertexID]], 1.0f);
}