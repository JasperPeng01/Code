#include <stdio.h>
#include <stdint.h>

int main() {
    float a = 59.622f;
    float b = 92.6327f;
    char buffer[4];  // 4字节数组，存两个数

    // 放大倍数，决定精度
    float scale = 1000.0f;

    // 将float转换成整数（16位）
    uint16_t A = (uint16_t)(a * scale + 0.5f);
    uint16_t B = (uint16_t)(b * scale + 0.5f);

    // 合成4字节数据，高16位存A，低16位存B
    uint32_t combined = ((uint32_t)A << 16) | B;

    // 存入char数组（按大端存储）
    buffer[0] = (combined >> 24) & 0xFF;
    buffer[1] = (combined >> 16) & 0xFF;
    buffer[2] = (combined >> 8) & 0xFF;
    buffer[3] = combined & 0xFF;

    // --- 从buffer提取回两个数 ---
    uint32_t extracted = ((uint8_t)buffer[0] << 24) | ((uint8_t)buffer[1] << 16) | ((uint8_t)buffer[2] << 8) | ((uint8_t)buffer[3]);

    uint16_t extractedA = (extracted >> 16) & 0xFFFF;
    uint16_t extractedB = extracted & 0xFFFF;

    // 还原为float
    float recoveredA = extractedA / scale;
    float recoveredB = extractedB / scale;

    // 输出结果
    printf("原始数据: %f, %f\n", a, b);
    printf("存储后的整数: %u, %u\n", A, B);
    printf("还原数据: %f, %f\n", recoveredA, recoveredB);
    printf("误差: %f, %f\n", a - recoveredA, b - recoveredB);

    return 0;
}
