#version 430 core
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout(rgba8, binding = 0) uniform image2D img_output;

void main() {
    vec4 pixel = vec4(1, 0, 0, 1);

    imageStore(img_output, ivec2(gl_GlobalInvocationID.xy), pixel);
}