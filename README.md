# Sculptor
# 🧊 Motor de Modelagem 3D: Escultor Virtual (Voxel Engine)

Este repositório contém a infraestrutura de um modelador tridimensional baseado em **voxels** escrito em `C++`. O sistema opera através da manipulação de uma matriz espacial discreta, permitindo a ativação, desativação e colorização de blocos em um espaço tridimensional, culminando na conversão dessa matriz de estados em uma malha geométrica real (formato `.OFF`).

## ⚙️ Arquitetura e Restrições de Memória

A gestão de memória é o núcleo crítico desta aplicação. O projeto obedece a uma API estrita que exige a alocação de uma matriz tridimensional fragmentada na memória *Heap* através de ponteiros triplos.

*   **Estrutura de Dados Atômica:** Cada unidade do espaço é representada pela `struct Voxel`, contendo propriedades de cor (`r`, `g`, `b`), opacidade (`a`) e estado lógico (`isOn`).
*   **Gerenciamento de Ciclo de Vida:** A classe `Sculptor` encapsula a complexidade da alocação de `Voxel ***v`. O construtor garante a inicialização segura em $\mathcal{O}(n_x \cdot n_y \cdot n_z)$ operações, enquanto o destrutor aplica a liberação reversa em cascata para garantir **zero vazamento de memória** (*memory leaks*).

## 🛠️ Funcionalidades Geométricas implementadas

A interface pública expõe métodos para desenho algorítmico, operando exclusivamente nos limites definidos na instanciação:

*   **Operações Atômicas:** `putVoxel` e `cutVoxel` para controle pontual.
*   **Primitivas Retangulares:** `putBox` e `cutBox` para blocos maciços.
*   **Primitivas Curvas:** `putSphere`, `cutSphere`, `putEllipsoid` e `cutEllipsoid`. (A lógica interna utiliza equações reduzidas de quádricas para determinar o pertencimento de cada voxel ao volume da figura).

## 🚀 Compilação e Execução

O código é independente de bibliotecas gráficas externas, exigindo apenas um compilador `C++` padrão (`g++`, `clang`, ou MSVC).


[Link do projeto](https://agostinhobritojr.github.io/curso/progav-dca3303/escultor.html)
