Clone from [Breakout](https://github.com/JonathanBack/breakout-game/tree/main) - By [JonathanBack](https://github.com/JonathanBack)

# 🎮 Breakout - Nebula Engine

Um clone clássico do jogo Breakout desenvolvido como protótipo para testar a **Nebula Engine** (game engine em Lua).

## 📋 Sobre o Projeto

Este é um jogo de Breakout funcional criado para testar e demonstrar as capacidades da Nebula Engine, incluindo:

- Sistema ECS (Entity Component System)
- Sistema de física e colisão
- Renderização de múltiplas entidades
- Input do teclado
- Game loop completo

## 🎯 Como Jogar

- **Setas ← →** ou **A/D**: Mover o paddle
- **R**: Reiniciar o jogo (quando perdeu ou ganhou)

## 🛠️ Características

- ✅ 50 blocos destrutíveis (5 linhas × 10 colunas)
- ✅ Sistema de colisão completo
- ✅ Física de reflexão da bola
- ✅ Efeito "inglês" no paddle (bola muda direção baseado onde bate)

## 🚀 Tecnologias

- **Linguagem**: Lua
- **Engine**: Nebula Engine (custom game engine)
- **Arquitetura**: ECS (Entity Component System)

## 📦 Estrutura

```
nebula/
├── main.lua          # Código principal do jogo
└── README.md         # Este arquivo
```

## 🎮 Componentes ECS Utilizados

- `Position`: Posição X/Y das entidades
- `Quad`: Renderização (largura e altura)
- `CollisionBox`: Detecção de colisão
- `Speed`: Velocidade de movimento
- `BlockActive`: Estado ativo/inativo dos blocos

## 🧪 Desenvolvido como Teste

Este jogo foi desenvolvido especificamente para testar e validar funcionalidades da Nebula Engine, incluindo:

- Sistema de componentes customizados
- Gerenciamento de múltiplas entidades (50+ objetos simultâneos)
- Sistema de física e colisões
- Loop de jogo e estados
- Sistema de input

## 📝 Licença

Este projeto é um protótipo de teste e está disponível como exemplo de uso da Nebula Engine.

---

