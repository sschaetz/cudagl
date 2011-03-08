__global__ void createVertices_kernel(float4* positions, float time,
  unsigned int width, unsigned int height)
{
  unsigned int x = blockIdx.x * blockDim.x + threadIdx.x;
  unsigned int y = blockIdx.y * blockDim.y + threadIdx.y;
  // Calculate uv coordinates
  float u = x / (float)width;
  float v = y / (float)height;
  u = u * 2.0f - 1.0f;
  v = v * 2.0f - 1.0f;
  // calculate simple sine wave pattern
  float freq = 4.0f;
  float w = sinf(u * freq + time)
  * cosf(v * freq + time) * 0.5f;
  // Write positions
  positions[y * width + x] = make_float4(u, w, v, 1.0f);
}

void createVertices(void * positions, float time,
  unsigned int width, unsigned int height)
{
  dim3 dimBlock(16, 16, 1);
  dim3 dimGrid(width / dimBlock.x, height / dimBlock.y, 1);
  createVertices_kernel<<<dimGrid, dimBlock>>>((float4*)positions, time,
    width, height);
  cudaDeviceSynchronize();
}
