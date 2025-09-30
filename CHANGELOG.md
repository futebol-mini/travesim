# Changelog

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Calendar Versioning](https://calver.org/).

Para a versão em PT-BR 🇧🇷 desse documento, veja [aqui](./CHANGELOG.pt-br.md)

## [25.09.2]

### Added

- Docker configuration files

## [25.09.1]

### Added

- Allow customization of robot physical parameters
- Clang-format as default C/C++ formatter

### Fixed

- Field load in RobotDev world
- Referee crash in RobotDev world

### Removed

- Uncrustify C++ formatter

## [25.08.1]

### Added

- Create world with 5 robots per team
- Improved README

### Removed

- Removed generic robots side walls
- Reduced hat size

### Fixed

- Robots now always initialize with zero velocity
- Include missing time info in step field in vision packets

## [25.07.1]

### Added

- Initial complete version 🎉
- Generic VSS robot model
- 3v3 match world file
- Single robot development world file
- VSS robot Webots controller
- Referee bridge controller
- Implement [VSS Proto](https://github.com/futebol-mini/VSSProto) standard

[25.07.1]: https://github.com/futebol-mini/travesim/releases/tag/v25.07.1
[25.08.1]: https://github.com/futebol-mini/travesim/releases/tag/v25.08.1
[25.09.1]: https://github.com/futebol-mini/travesim/releases/tag/v25.09.1
[25.09.2]: https://github.com/futebol-mini/travesim/releases/tag/v25.09.2
