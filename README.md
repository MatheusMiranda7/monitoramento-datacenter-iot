# Sistema Inteligente de Monitoramento Ambiental para Data Centers Urbanos

## Descrição

Projeto desenvolvido utilizando ESP32, sensor DHT22 e protocolo MQTT para monitoramento inteligente de temperatura e umidade em data centers urbanos.

O sistema realiza o monitoramento em tempo real e aciona automaticamente um sistema de ventilação através de um módulo relé quando a temperatura ultrapassa o limite estabelecido.

## Objetivo

Contribuir para a eficiência energética e sustentabilidade urbana, alinhado ao ODS 11 da ONU.

## Hardware Utilizado

- ESP32 DevKit
- Sensor DHT22
- Módulo Relé
- LED
- Resistor 10kΩ
- Protoboard
- Jumpers

## Software Utilizado

- Arduino IDE
- Wokwi
- HiveMQ
- MQTT
- Fritzing

## Funcionamento

1. O DHT22 realiza a leitura da temperatura e umidade.
2. O ESP32 processa os dados.
3. Os dados são enviados via MQTT.
4. O HiveMQ recebe as mensagens.
5. Caso a temperatura ultrapasse 30°C, o relé é acionado.

## Tópicos MQTT

- matheus/datacenter/temperatura
- matheus/datacenter/umidade
- matheus/datacenter/alerta

## Comunicação

O sistema utiliza protocolo MQTT sobre TCP/IP via Wi-Fi integrado ao ESP32.

## Resultados

O sistema apresentou baixa latência e funcionamento em tempo real durante os testes realizados.

## Autor

Matheus Miranda Ferreira
Universidade Presbiteriana Mackenzie
2026
