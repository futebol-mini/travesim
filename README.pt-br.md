<h1 align="center">🥅 TraveSim</h1>
<p align="center">Projeto de simuação de IEEE Very Small Size Soccer com Webots</p>

<p align="center">

<img alt="Science" src="https://img.shields.io/badge/Built_with-Science-orange?style=for-the-badge&labelColor=e46c17&color=d35b09">

<img src="https://img.shields.io/badge/calver-YY.0M.MINOR-blue?style=for-the-badge" href="https://calver.org/" alt="Calver" />

<img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" href="./LICENSE.md" alt="License MIT" />

<!-- ALL-CONTRIBUTORS-BADGE:START - Do not remove or modify this section -->
<img src="https://img.shields.io/badge/all_contributors-11-orange.svg?style=for-the-badge" href="#-contributors" alt="All contributors"/>
<!-- ALL-CONTRIBUTORS-BADGE:END -->

</p>

<!-- TOC -->

- [📷 Screenshots](#-screenshots)
- [🎈 Intro](#-intro)
- [➕ Dependẽncias](#-dependẽncias)
- [🌎 Mundos](#-mundos)
- [📣 Comunicação](#-comunicação)
- [📏 Modelos utilizados](#-modelos-utilizados)
  - [📜 Parâmetros principais](#-parâmetros-principais)
  - [⚙️ Parâmetros dos motores](#️-parâmetros-dos-motores)
- [📁 Estrutura das pastas](#-estrutura-das-pastas)
- [📝 Contribuindo](#-contribuindo)
- [✨ Contribuidores](#-contribuidores)

<!-- /TOC -->

## 📷 Screenshots

<p align="center">
  <img height=300px src="./docs/Match3v3.png" alt="Match3v3"/>
</p>

## 🎈 Intro

This project is the spiritual successor of the [classic Travesim](https://github.com/ThundeRatz/travesim)

The environment is built upon [Webots](https://cyberbotics.com/), an open source general purpouse robotics simulator

## ➕ Dependẽncias

Instale [Webots](https://cyberbotics.com/doc/guide/installation-procedure#installing-the-debian-package-with-the-advanced-packaging-tool-apt) no seu sistema. Para distribuições baseadas em Debian, rode os comandos:

```bash
sudo mkdir -p /etc/apt/keyrings
cd /etc/apt/keyrings
sudo wget -q https://cyberbotics.com/Cyberbotics.asc

echo "deb [arch=amd64 signed-by=/etc/apt/keyrings/Cyberbotics.asc] https://cyberbotics.com/debian binary-amd64/" | sudo tee /etc/apt/sources.list.d/Cyberbotics.list
sudo apt update

sudo apt install -y webots cmake libboost-system-dev libboost-thread-dev protobuf-compiler
```

> [!WARNING]
> Se o Webots for instalado de outra forma, será necessário configurar a variável de ambiente `WEBOTS_HOME` de acordo

Em seguida, clone o repo com:

```bash
git clone https://github.com/futebol-mini/travesim.git
```

Por fim, compile os controladores com:

```bash
cd travesim
make
```

## 🌎 Mundos

Na versão atual, o TraveSim consegue executar jogos com 3 robôs em cada time. No futuro próximo, planejamos migrar o campo para partidas 5v5

Os seguintes mundos estão implementados:

-`Match3v3.wbt` - Mundo base para partidas 3v3
-`RobotDev.wbt` - Mundo de desenvolvimento com um único robô

## 📣 Comunicação

Os controladores do TraveSim seguem o padrão [VSSProto](https://github.com/futebol-mini/VSSProto)

## 📏 Modelos utilizados

O TraveSim utiliza um modelo de robô VSS genérico, definido em `protos/GenericVssRobot.proto`

O esquema de cores dos robôs segue o padrão definido nas regras da IEEE Latin American Robotics Competition

### 📜 Parâmetros principais

As propriedades do robô foram determinadas usando materiais típicos usados em robôs do mundo real

|          Parâmetro           |          Valor | Unidade |
|:----------------------------:|---------------:|:--------|
|         Raio da roda         |             25 | mm      |
|      Espessura da roda       |              8 | mm      |
|     Separação das rodas      |             55 | mm      |
|     Densidade das rodas      |           1150 | kg/m³   |
|      Massa de cada roda      |             18 | g       |
|      Material das rodas      |          Nylon | \-      |
|      Material do corpo       | 50% infill ABS | \-      |
|      Densidade do corpo      |            510 | kg/m³   |
|         Altura total         |             62 | mm      |
|        Largura total         |             78 | mm      |
|      Comprimento total       |             78 | mm      |
|         Massa total          |            180 | g       |
| Momento de inércia total Izz |          0.113 | g m²    |

### ⚙️ Parâmetros dos motores

O modelo do motor é inspirado no motor [Pololu 50:1 Micro Metal Gearmotor](https://www.pololu.com/product/3073) de modo a obter valures realistas

|             Parâmetro             | Valor | Unidade |
|:---------------------------------:|------:|:--------|
|           Torque máximo           |    73 | mN m    |
| Aceleração linear máxima do robô  |    16 | m/s²    |
| Aceleração angular máxima do robô |  1420 | rad/s²  |
|          Rotação máxima           |   650 | RPM     |
|          Rotação máxima           |    68 | rad/s   |
| Velocidade linear máxima do robô  |   1.7 | m/s     |
| Velocidade angular máxima do robô |   9.8 | rad/s   |

## 📁 Estrutura das pastas

- **controllers/** - Pasta de controladores Webots
  - **common/** - Interfaces comuns a todos os controladores. Estrutura das mensagens enviadas via [Webots emitters](https://www.cyberbotics.com/doc/reference/emitter).
  - **referee_controller/** - [Webots supervisor](https://www.cyberbotics.com/doc/reference/supervisor) para intermediar comandos dos times e do referee para a simulação.
  - **vss_robot_controller/** - Controlador individual dos robôs
- **protos/** - Arquivos [Webots PROTO](https://cyberbotics.com/doc/reference/proto) que descrevem os robôs, o campo e a bola
- **worlds/** - [Arquivos de mundo Webots](https://cyberbotics.com/doc/reference/webots-world-files) para simulação das partidas

## 📝 Contribuindo

Toda ajuda no desenvolvimento da robótica é bem vinda, nós incentivamos você a contribuir para o projeto! Para saber como, veja as [diretrizes de contribuição](CONTRIBUTING.pt-br.md)

## ✨ Contribuidores

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tbody>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/FelipeGdM"><img src="https://avatars3.githubusercontent.com/u/1054087?v=4?s=100" width="100px;" alt="Felipe Gomes de Melo"/><br /><sub><b>Felipe Gomes de Melo</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/commits?author=FelipeGdM" title="Documentation">📖</a> <a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3AFelipeGdM" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/futebol-mini/travesim/commits?author=FelipeGdM" title="Code">💻</a> <a href="#translation-FelipeGdM" title="Translation">🌍</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/LucasHaug"><img src="https://avatars3.githubusercontent.com/u/39196309?v=4?s=100" width="100px;" alt="Lucas Haug"/><br /><sub><b>Lucas Haug</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3ALucasHaug" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/futebol-mini/travesim/commits?author=LucasHaug" title="Code">💻</a> <a href="#translation-LucasHaug" title="Translation">🌍</a> <a href="https://github.com/futebol-mini/travesim/commits?author=LucasHaug" title="Documentation">📖</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Tocoquinho"><img src="https://avatars2.githubusercontent.com/u/37677881?v=4?s=100" width="100px;" alt="tocoquinho"/><br /><sub><b>tocoquinho</b></sub></a><br /><a href="#ideas-Tocoquinho" title="Ideas, Planning, & Feedback">🤔</a> <a href="https://github.com/futebol-mini/travesim/commits?author=Tocoquinho" title="Documentation">📖</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/Berbardo"><img src="https://avatars0.githubusercontent.com/u/48636340?v=4?s=100" width="100px;" alt="Bernardo Coutinho"/><br /><sub><b>Bernardo Coutinho</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3ABerbardo" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/futebol-mini/travesim/commits?author=Berbardo" title="Code">💻</a> <a href="https://github.com/futebol-mini/travesim/commits?author=Berbardo" title="Documentation">📖</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/lucastrschneider"><img src="https://avatars0.githubusercontent.com/u/50970346?v=4?s=100" width="100px;" alt="Lucas Schneider"/><br /><sub><b>Lucas Schneider</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3Alucastrschneider" title="Reviewed Pull Requests">👀</a> <a href="https://github.com/futebol-mini/travesim/commits?author=lucastrschneider" title="Code">💻</a> <a href="#translation-lucastrschneider" title="Translation">🌍</a> <a href="https://github.com/futebol-mini/travesim/commits?author=lucastrschneider" title="Documentation">📖</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/JuliaMdA"><img src="https://avatars1.githubusercontent.com/u/65100162?v=4?s=100" width="100px;" alt="Júlia Mello"/><br /><sub><b>Júlia Mello</b></sub></a><br /><a href="#design-JuliaMdA" title="Design">🎨</a> <a href="#data-JuliaMdA" title="Data">🔣</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/ThallesCarneiro"><img src="https://avatars1.githubusercontent.com/u/71659373?v=4?s=100" width="100px;" alt="ThallesCarneiro"/><br /><sub><b>ThallesCarneiro</b></sub></a><br /><a href="#design-ThallesCarneiro" title="Design">🎨</a> <a href="#data-ThallesCarneiro" title="Data">🔣</a></td>
    </tr>
    <tr>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/TetsuoTakahashi"><img src="https://avatars2.githubusercontent.com/u/38441802?v=4?s=100" width="100px;" alt="TetsuoTakahashi"/><br /><sub><b>TetsuoTakahashi</b></sub></a><br /><a href="#ideas-TetsuoTakahashi" title="Ideas, Planning, & Feedback">🤔</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/GabrielCosme"><img src="https://avatars0.githubusercontent.com/u/62270066?v=4?s=100" width="100px;" alt="Gabriel Cosme Barbosa"/><br /><sub><b>Gabriel Cosme Barbosa</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3AGabrielCosme" title="Reviewed Pull Requests">👀</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/RicardoHonda"><img src="https://avatars1.githubusercontent.com/u/62343088?v=4?s=100" width="100px;" alt="RicardoHonda"/><br /><sub><b>RicardoHonda</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3ARicardoHonda" title="Reviewed Pull Requests">👀</a></td>
      <td align="center" valign="top" width="14.28%"><a href="https://github.com/leticiakimoto"><img src="https://avatars0.githubusercontent.com/u/62733251?v=4?s=100" width="100px;" alt="leticiakimoto"/><br /><sub><b>leticiakimoto</b></sub></a><br /><a href="https://github.com/futebol-mini/travesim/pulls?q=is%3Apr+reviewed-by%3Aleticiakimoto" title="Reviewed Pull Requests">👀</a></td>
    </tr>
  </tbody>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->
