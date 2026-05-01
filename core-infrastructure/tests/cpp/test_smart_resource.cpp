#define ANSI_RESET "\033[0m"
/**
 * @author Cristiano
 * @date 2026
 */
#include <gtest/gtest.h>
#include "../../repositorio-extra/atividade-extra59/SmartResource.h"
#include <memory>

/**
 * @file test_smart_resource.cpp
 * @brief Testes Unitários Industriais para SmartResource.
 */

TEST(SmartResourceTest, OwnershipTransfer) {
    auto resource = std::make_unique<SmartResource>("GPS_MODULE_01");
    EXPECT_EQ(resource->getId(), "GPS_MODULE_01");
    
    // Teste de movimentação (Unique Ownership)
    auto new_owner = std::move(resource);
    EXPECT_EQ(resource, nullptr);
    EXPECT_EQ(new_owner->getId(), "GPS_MODULE_01");
}

TEST(SmartResourceTest, SharedResourceCount) {
    auto shared_res = std::make_shared<SmartResource>("SENSOR_TEMP_05");
    EXPECT_EQ(shared_res.use_count(), 1);
    
    {
        auto second_owner = shared_res;
        EXPECT_EQ(shared_res.use_count(), 2);
    }
    
    EXPECT_EQ(shared_res.use_count(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
/**
 * @section MemoryMap
 * Stack: variáveis locais e ponteiros. Heap: alocações via Smart Pointers/RAII.
 */

/*
 * RESUMO TEÓRICO
 * Alinhado com o Padrão de Entrega de Elite (Protocolo GEMINI).
 */
