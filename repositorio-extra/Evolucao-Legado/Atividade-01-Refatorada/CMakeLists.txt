# Executável da Atividade 01 Refatorada (Padrão Industrial)
add_executable(Evolucao-Atividade-01 
    main_refatorado.cpp 
    Produto.cpp 
    GestorEstoque.cpp
)

# Organização na IDE
set_target_properties(Evolucao-Atividade-01 PROPERTIES FOLDER "Evolucao/Atividade-01")
