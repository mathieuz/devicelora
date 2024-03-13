# LORALIB
Biblioteca de configuração e desenvolvimento de firmwares customizados baseada na API RUI3 da Placa RAK3172.

## Sumário
+ [Requisitos e Configurações Prévias](#requisitos-e-configurações-prévias)
  - [Tutoriais de Configuração](#tutoriais-de-configuração)
+ [Instalando a Biblioteca](#instalando-a-biblioteca)
+ [Utilização](#utilização)
  - [Iniciando conexão no Modo ABP](#iniciando-conexão-no-modo-abp)
  - [Iniciando conexão no Modo OTAA](#iniciando-conexão-no-modo-otaa)
+ [Multicast](#multicast)
  - [AddMulticastGroup()](#addmulticastgroup)
  - [RemoveMulticastGroup()](#removemulticastgroup)
  - [ListMulticastGroups()](#listmulticastgroups)
+ [Comandos e Funcionalidades](#comandos-e-funcionalidades)
  + [Modo ABP](#modo-abp)
    - [SetAppskey()](#setappskey)
    - [SetNwkskey()](#setnwkskey)
    - [SetDeviceAddress()](#setdeviceaddress)
  + [Modo OTAA](#modo-otaa)
    - [GetAppkey()](#getappkey)
    - [SetAppkey()](#setappkey)
  + [Geral](#geral)
    - [Setup()](#setup)
    - [SetupFlash()](#setupflash)
    - [GetIosModes()](#getiosmodes)
    - [GetIosZones()](#getioszones)
    - [GetTimersZones()](#gettimerszones)
    - [GetIoConfig()](#getioconfig)
    - [GetTimer0()](#gettimer0)
    - [GetTimer1()](#gettimer1)
    - [GetTimer2()](#gettimer2)
    - [GetTimer3()](#gettimer3)
    - [GetTimer4()](#gettimer4)
    - [SendData()](#senddata)
    - [GetDeviceEUI()](#getdeviceeui)
    - [SetDeviceEUI()](#setdeviceeui)
    - [GetAppskey()](#getappskey)
    - [GetNwkskey()](#getnwkskey)
    - [GetDeviceAddress()](#getdeviceaddress)
    - [GetJoinMode()](#getjoinmode)
    - [GetNetworkJoinStatus()](#getnetworkjoinstatus)
    - [GetConfirmMode()](#getconfirmmode)
    - [SetConfirmMode()](#setconfirmmode)
    - [GetNumberOfRetransmissions()](#getnumberofretransmissions)
    - [SetNumberOfRetransmissions()](#setnumberofretransmissions)
    - [GetActiveRegion()](#getactiveregion)
    - [SetActiveRegion()](#setactiveregion)
    - [GetClass()](#getclass)
    - [SetClass()](#setclass)
    - [GetBatteryLevel()](#getbatterylevel)
    - [SleepAll()](#sleepall)
    - [SleepCPU()](#sleepcpu)
    - [SleepLoRa()](#sleeplora)
    - [SetChannelMask()](#setchannelmask)

## Requisitos e Configurações Prévias
Para a utilização dessa biblioteca, é necessário ter instalado o Arduino IDE.

Uma vez instalado, é preciso obter as placas que possuem suporte para a utilização da API RUI3, encontrados dentro do Arduino IDE.

### Tutoriais de Configuração:
- [Instalação do Arduino IDE](https://docs.rakwireless.com/RUI3/Supported-IDE/#arduino-installation)
- [Instalação e configuração das placas no Arduino IDE](https://docs.rakwireless.com/RUI3/Supported-IDE/#install-rui3-board-support-package-in-arduino-ide)

Ao finalizar, as placas com suporte ao RUI3 estarão disponíveis para uso dentro do editor de código. Isso vai permitir o uso da biblioteca sem problemas.

<br>

## Instalando a Biblioteca
Todos os arquivos e componentes da biblioteca estão armazenados em um arquivo .zip chamado 'loralib.zip', disponível neste diretório. Este arquivo pode ser carregado como uma biblioteca dentro do Arduino IDE da seguinte forma:

1. Baixe o arquivo 'loralib.zip';
2. Abra o Arduino IDE em um sketch vazio. Na barra de menu superior, vá para **Sketch > Include Library > Add .ZIP Library**. Na janela aberta, localize e selecione o .zip da biblioteca.

Uma guia chamada 'Output' será aberta no Arduino IDE com a mensagem 'Library Installed'. Isso significa que a biblioteca foi instalada com sucesso.

3. Siga novamente para **Sketch > Include Library**. Dessa vez, localize no menu a seção 'Contributed libraries', na parte inferior, e clique em 'devicelora'.

Isso vai adicionar as classes principais da biblioteca para o projeto. O código em branco do Sketch estará assim:

```cpp
#include <DeviceLora.h>
#include <DeviceLoraABP.h>
#include <DeviceLoraOTAA.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
```

<br>

## Utilização
A biblioteca é composta por três arquivos de classe principais. Duas delas são utilizadas para criar instâncias de conexão e comunicação com os dispositivos LoRa e foram baseadas nos modos de conexão disponíveis: ABP ou OTAA. O processo de iniciar uma conexão é o mesmo para ambos os modos, o que muda é apenas os parâmetros de conexão. Veja:


### Iniciando conexão no Modo ABP
Para isso, basta instanciar um novo objeto da classe `DeviceLoraABP`, passando os parâmetros de inicialização principais.

```cs
DeviceLoraABP abp(string deviceAddress, string AppSKey, string NwkSKey, string DeviceEUI, char ClassMode, uint16_t channelMask);
```

No Modo ABP, as chaves de conexão (Device Address, AppSKey, NwkSKey e Device EUI) devem ser informadas manualmente. Além das chaves de ativação, é preciso informar a classe de operação (A, B ou C) e a máscara de canal (Channel Mask) (ver [SetChannelMask()](#setchannelmask) para mais detalhes).

Uma vez que uma conexão no modo ABP é instanciada, basta executar a função `Setup()` do objeto dentro do bloco `void Setup()`. Isso vai permitir iniciar a conexão efetivamente com o dispositivo associado as chaves de ativação.

```cpp
#include <DeviceLora.h>
#include <DeviceLoraABP.h>
#include <DeviceLoraOTAA.h>

//Instanciando objeto de conexão
DeviceLoraABP abp("0527236b", "0b61af04bc20bb1d163affd7016730b3", "c211a27f564d790f6e3757c5db2ae008", "AC1F09FFFE0B6091", 'C', 0x0001);

void setup() {
    Serial.begin(115200); //Definindo Baudrate
    abp.Setup(); //Iniciando conexão.
}

void loop() {

}
```

À partir daí, todos os outros métodos acessados pelo objeto instanciado poderão ser utilizados.

### Iniciando conexão no Modo OTAA
No modo OTAA, as chaves de conexão (Device Address, AppSKey, NwkSKey) são gerados automaticamente ao se conectar, o que torna necessário informar apenas o Appkey, o Device EUI do dispositivo, a classe de operação para iniciar uma conexão neste modo e a máscara de canal (ver [SetChannelMask()](#setchannelmask) para mais detalhes).

```cs
DeviceLoraOTAA otaa(string Appkey, string DeviceEUI, char ClassMode, uint16_t channelMask);
```

Assim como no modo ABP, a conexão é iniciada chamando a função `Setup()`, acessada do objeto de conexão instanciado, dentro do bloco `void Setup()`.

```cpp
#include <DeviceLora.h>
#include <DeviceLoraABP.h>
#include <DeviceLoraOTAA.h>

//Instanciando objeto de conexão
DeviceLoraOTAA otaa("ccf296647c4997bc6c1bbaba5d23543f", "AC1F09FFFE0B6091", 'C', 0x0001);

void setup() {
    Serial.begin(115200); //Definindo Baudrate
    otaa.Setup(); //Iniciando conexão
}

void loop() {

}
```

A conexão no modo OTAA ocorre de forma assíncrona, o que significa que a rotina de `Setup()` continuará executando até que o dispositivo esteja conectado.

No monitor serial, é possível visualizar todas as tentativas falhas de conexão neste modo. A mensagem exibida neste caso é essa:

```
+EVT:JOIN_FAILED_RX_TIMEOUT
Status do Join: 4
```

O dispositivo estará conectado apenas quando a seguinte mensagem aparecer:

```
+EVT:JOINED
Status do Join: 0
```

Uma vez conectado, todas as instruções seguintes serão executadas normalmente.

<br>

## Multicast
É possível também configurar e gerenciar grupos de multicast associados a um dispositivo através de uma série de métodos específicos. Configurar grupos de multicast permite o recebimento de mensagens via downlink para um grupo de dispositivos em comum.

Há três métodos associados ao gerenciamento de grupos de multicast que podem ser acessados e utilizados a partir de uma instância de conexão:

- **`AddMulticastGroup()`** - adiciona grupos de multicast para um dispositivo.
- **`RemoveMulticastGroup()`** - remove um grupo de multicast do dispositivo.
- **`ListMulticastGroups()`** - lista todos os grupos de multicast adicionados em um dispositivo.

<br>

### AddMulticastGroup()
Método que adiciona um grupo de multicast existente para um dispositivo. É necessário passar todas as chaves e parâmetros de um grupo de multicast existente.

```cs
AddMulticastGroup(char mcDeviceClass, string mcAddress, string mcNwkskey, string mcAppskey, uint mcFrequency, uint mcDatarate, uint mcPeriodicity, uint mcGroupID, uint mcEntry);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instanciando objeto de conexão.
DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);
    
    Serial.begin(115200); //Definindo Baudrate
    abp.Setup(); //Instanciando conexão

    //Adicionando grupo de multicast no dispositivo
    abp.AddMulticastGroup('C', "aabbccdd", "31bb0739b191b43663e141664ce706e2", "5f2fb2119333ce6c3b0482f85c9d1f46", 923300000, 8, 0, 4, 0);
}

void loop()
{

}
```

Ao finalizar o upload, uma mensagem no monitor serial será exibido:

```
Grupo de multicast adicionado com sucesso!
Current Work Mode: LoRaWAN.
```

Essa mensagem é visualizada graças ao tempo definido em `delay(5000)`, que aguarda 5 segundos antes de executar todo os outros comandos seguintes. É possível visualizar grupos adicionados via comando `AT+LSTMULC=?` ou pelo método `ListMulticastGroups()`.

<br><hr><br>

### RemoveMulticastGroup()
Este método remove um grupo de multicast adicionado ao dispositivo informando seu Multicast Address (mcAddress).

```cs
RemoveMulticastGroup(string mcAddress);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instanciando objeto de conexão.
DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);
    
    Serial.begin(115200); //Definindo Baudrate
    abp.Setup(); //Instanciando conexão

    //Adicionando grupo de multicast no dispositivo
    abp.AddMulticastGroup('C', "aabbccdd", "31bb0739b191b43663e141664ce706e2", "5f2fb2119333ce6c3b0482f85c9d1f46", 923300000, 8, 0, 4, 0);

    delay(3000);

    //Removendo grupo de multicast adicionado anteriormente.
    abp.RemoveMulticastGroup("aabbccdd");
}

void loop()
{

}
```

Ao finalizar o upload, uma mensagem no monitor serial será exibido:

```
Grupo de multicast adicionado com sucesso!
Grupo de multicast removido com sucesso!
Current Work Mode: LoRaWAN.
```

No código de exemplo, um grupo de multicast é adicionado e 3 segundos depois é removido. É graças aos comandos de `delay()` que é possível visualizar essas mensagens.

<br><hr><br>

### ListMulticastGroups()
Lista todos os grupos de multicast adicionados no dispositivo.

```cs
ListMulticastGroups();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instanciando objeto de conexão.
DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);
    
    Serial.begin(115200); //Definindo Baudrate
    abp.Setup(); //Instanciando conexão

    //Adicionando grupo de multicast no dispositivo
    abp.AddMulticastGroup('C', "aabbccdd", "31bb0739b191b43663e141664ce706e2", "5f2fb2119333ce6c3b0482f85c9d1f46", 923300000, 8, 0, 4, 0);

    delay(3000);

    //Listando grupos de multicast adicionado no dispositivo.
    abp.ListMulticastGroups();
}

void loop()
{

}
```

Ao finalizar o upload, uma mensagem no monitor serial será exibido:

```
Grupo de multicast adicionado com sucesso!
Multicast Device Class = 2
Multicast Device Address = AABBCCDD
Multicast APPSKEY = 5F2FB2119333CE6C3B0482F85C9D1F46
Multicast NWKSKEY = 31BB0739B191B43663E141664CE706E2
Frequencia = 923300000
Data Rate = 8
Periodicidade = 0
Entry = 1

Current Work Mode: LoRaWAN.
```

No código de exemplo, um grupo de multicast é adicionado e em seguida é listado todos os grupos de multicast adicionados no dispositivo.

<br>

## Comandos e Funcionalidades
Todos os métodos disponíveis para uso até agora.

## Modo ABP
### SetAppskey()
Define a chave AppSKey do dispositivo à partir de uma sequência hexadecimal de 32 caracteres.

```cs
SetAppskey(string appskey);
```

**Exemplo:**
```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    Serial.begin(115200);
    abp.Setup();

    //Definindo Appskey.
    abp.SetAppskey("ff300b61bc20bb1da4d701b0163af673");
}

void loop()
{

}
```

<br><hr><br>

### SetNwkskey()
Define a chave NwkSKey do dispositivo à partir de uma sequência hexadecimal de 32 caracteres.

```cs
SetNwkskey(string nwkskey);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    Serial.begin(115200);
    abp.Setup();

    //Definindo Nwkskey.
    abp.SetNwkskey("0b61204d7ff3001bbc01f67363bdb1aa");
}

void loop()
{

}
```

<br><hr><br>

### SetDeviceAddress()
Define o Device Address do dispositivo à partir de uma sequência hexadecimal de 8 caracteres.

```cs
SetDeviceAddress(string deviceAddress);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("023627b5", "3004bc20bb1d1b0b61affd70163af673", "564d90f6e3757c5dc211a27fae00b287", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    Serial.begin(115200);
    abp.Setup();

    //Definindo Device Address.
    abp.SetDeviceAddress("a1a2a3a4");
}

void loop()
{

}
```

<br>

## Modo OTAA
### GetAppkey()
Retorna a chave Appkey do dispositivo.

```cs
GetAppkey();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraOTAA otaa("354966473fc1bcf2bcc4c6ab997ba5d2", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    otaa.Setup();

    //Retornando Appkey do dispositivo.
    Serial.println(otaa.GetAppkey());

}

void loop()
{

}
```

**Saída no monitor serial:**

```
354966473FC1BCF2BCC4C6AB997BA5D2
```

<br><hr><br>

### SetAppkey()
Define o Appkey do dispositivo à partir de uma sequência hexadecimal de 32 caracteres.

```cs
SetAppkey(string appkey);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraOTAA otaa("354966473fc1bcf2bcc4c6ab997ba5d2", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    otaa.Setup();

    //Definindo Appkey.
    otaa.SetAppkey("647496fc6ab99f2b1b7b335cc4cca5d2");

}

void loop()
{

}
```

<br>

## Geral

### Setup()
Inicia conexão à partir de uma instância de objeto (ABP ou OTAA).

```cs
Setup();
```

**Exemplo:**

```cpp
#include <DeviceLora.h>
#include <DeviceLoraABP.h>
#include <DeviceLoraOTAA.h>

//Instanciando objeto de conexão
DeviceLoraABP abp("0527236b", "0b61af04bc20bb1d163affd7016730b3", "c211a27f564d790f6e3757c5db2ae008", "AC1F09FFFE0B6091", 'C', 0x0001);

void setup() {
    Serial.begin(115200); //Definindo Baudrate
    abp.Setup(); //Iniciando conexão.
}

void loop() {

}
```

<br><hr><br>

### SetupFlash()
Inicializa os modos e zonas dos IOs e os tempos dos timers de zona na memória flash do dispositivo.

```cs
SetupFlash();
```

Para inicializá-los, a execução do sketch aguardará 5 segundos até que as informações de configuração sejam enviadas via serial para o dispositivo. Caso contrário, a execução do sketch seguirá normalmente.

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();

}

void loop() {

} 
```

Uma vez que as informações de configuração são recebidas na serial dentro deste intervalo, esses dados serão gravados em uma sequência de bytes dentro da memória flash do dispositivo, das quais podem ser consultadas por outros métodos de classe.

<br><hr><br>

### GetIosModes()
Exibe os estados lógicos dos pinos IOs.

```cs
GetIoModes();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);


void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();

}

void loop() {
    abp.GetIosModes();
    delay(4000);
} 
```

**Saída no monitor serial:**

```
Modos dos IOs:
PA15: (Saida Digital)
PA1: (Entrada Analogica)
PA8: (Entrada Digital)
PA9: (Entrada Analogica)
PA0: (Entrada Digital)
PB5: (Saida Digital)
PB4: (Saida Digital)
PB3: (Entrada Digital)
PA2: (Entrada Analogica)
PB12: (Saida Digital)
```

<br><hr><br>

### GetIosZones()
Exibe as zonas definidas dos pinos IOs.

```cs
GetIosZones();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);


void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();

}

void loop() {
    abp.GetIosZones();
    delay(4000);
} 
```

**Saída no monitor serial:**

```
PA15: Zona 3
PA1: Zona 0
PA8: Zona 2
PA9: Zona 0
PA0: Zona 4
PB5: Zona 0
PB4: Zona 1
PB3: Zona 3
PA2: Zona 3
PB12: Zona 2
```

<br><hr><br>

### GetTimersZones()
Exibe o valor de timer das zonas.

```cs
GetTimersZones();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);


void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();

}

void loop() {
    abp.GetTimersZones();
    delay(4000);
} 
```

**Saída no monitor serial:**

```
Timers definidos nos IOs:
Zona 0: 2540
Zona 1: 3452
Zona 2: 4586
Zona 3: 5869
Zona 4: 6774
```

<br><hr><br>

### GetIoConfig()
Exibe detalhadamente as configurações dos IOs na flash, de acordo com a zona associada.

```cp
GetIoConfig(uint8_t zone);
```

Este método deve ser utilizado e associado com os handlers de cada zona disponível para executar uma função de acordo com o seu valor de tempo. As zonas vão de 0 a 4 e cada uma possui um valor de tempo que executa suas funções handlers associadas, valor de tempo esse acessado por métodos **GetTimer** da classe de instância de conexão.

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

//Timer handlers
void timer0 (void* data) { abp.GetIoConfig(0); }
void timer1 (void* data) { abp.GetIoConfig(1); }
void timer2 (void* data) { abp.GetIoConfig(2); }
void timer3 (void* data) { abp.GetIoConfig(3); }
void timer4 (void* data) { abp.GetIoConfig(4); }

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();

    //Registrando os timer handlers.
    api.system.timer.create(RAK_TIMER_0, (RAK_TIMER_HANDLER)timer0, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_0, abp.GetTimer0(), NULL);

    api.system.timer.create(RAK_TIMER_1, (RAK_TIMER_HANDLER)timer1, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_1, abp.GetTimer1(), NULL);

    api.system.timer.create(RAK_TIMER_2, (RAK_TIMER_HANDLER)timer2, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_2, abp.GetTimer2(), NULL);

    api.system.timer.create(RAK_TIMER_3, (RAK_TIMER_HANDLER)timer3, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_3, abp.GetTimer3(), NULL);

    api.system.timer.create(RAK_TIMER_4, (RAK_TIMER_HANDLER)timer4, RAK_TIMER_ONESHOT);
    api.system.timer.start(RAK_TIMER_4, abp.GetTimer4(), NULL);

}

void loop() {

} 
```

Os métodos **GetTimer** (`GetTimer0()`, `GetTimer1()`, etc.) retornam o valor do timer atual gravado na memória flash do dispositivo. Esse valor define quanto tempo o handler precisa esperar para ser executado (uma vez que no registro dos handlers no `Setup`, o modo configurado é o `RAK_TIMER_ONESHOT`, que possui esse comportamento de executar uma vez dentro desse tempo limite). O método `GetIoConfig()` recebe o valor da zona e é chamado dentro de seus handlers, também associados a uma zona. Isso vai retornar na serial, dentro de cada tempo definido, as configurações de modo dos IOs e em que cada zona eles pertencem.

**Saída no monitor serial:**

```
Current Work Mode: LoRaWAN.

IOs associados a zona/timer ID 0 (tempo do timer definido: 2000)
PA8 (Saida Digital)
PA9 (Saida Digital)

IOs associados a zona/timer ID 1 (tempo do timer definido: 4000)

IOs associados a zona/timer ID 2 (tempo do timer definido: 6000)
PA15 (Saida Digital)
PA0 (Entrada Analogica)
PB3 (Entrada Digital)

IOs associados a zona/timer ID 3 (tempo do timer definido: 8000)
PB5 (Entrada Analogica)
PB4 (Entrada Analogica)
PB12 (Entrada Analogica)

IOs associados a zona/timer ID 4 (tempo do timer definido: 14000)
PA1 (Entrada Analogica)
PA2 (Saida Digital)
```

<br><hr><br>

### GetTimer0()
Retorna o valor definido como tempo na zona 0.

```cs
GetTimer0();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();
    
}

void loop() {
    Serial.print("Tempo definido na zona 0: ");
    Serial.println(abp.GetTimer0());
    delay(3000);
} 
```

<br><hr><br>

### GetTimer1()
Retorna o valor definido como tempo na zona 1.

```cs
GetTimer1();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();
    
}

void loop() {
    Serial.print("Tempo definido na zona 1: ");
    Serial.println(abp.GetTimer1());
    delay(3000);
} 
```

<br><hr><br>

### GetTimer2()
Retorna o valor definido como tempo na zona 2.

```cs
GetTimer2();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();
    
}

void loop() {
    Serial.print("Tempo definido na zona 2: ");
    Serial.println(abp.GetTimer2());
    delay(3000);
} 
```

<br><hr><br>

### GetTimer3()
Retorna o valor definido como tempo na zona 3.

```cs
GetTimer3();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();
    
}

void loop() {
    Serial.print("Tempo definido na zona 3: ");
    Serial.println(abp.GetTimer3());
    delay(3000);
} 
```

<br><hr><br>

### GetTimer4()
Retorna o valor definido como tempo na zona 4.

```cs
GetTimer4();
```

**Exemplo:**

```cpp
#include "DeviceLora.h"
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

//Instância de conexão LoRa.
DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup() {
    Serial.begin(115200);

    //Finalizando instância de conexão.
    abp.Setup();

    //Aguarda os bytes das configurações dos IOs por 5 segundos.
    abp.SetupFlash();
    
}

void loop() {
    Serial.print("Tempo definido na zona 4: ");
    Serial.println(abp.GetTimer4());
    delay(3000);
} 
```

<br><hr><br>

### SendData()
Envia texto via uplink para uma porta especificada. É possível definir número de tentativas de envio da informação.

```cs
SendData(int port, string data, int retries);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    Serial.begin(115200);
    abp.Setup();

}

void loop()
{
    //Enviando "TesteSend123" na porta 8 em 7 tentativas de envio.
    delay(5000);
    abp.SendData(8, "TesteSend123", 7);
}
```

**Saída no monitor serial:**

```
Status do Send: 4
+EVT:SEND_CONFIRMED_FAILED(4)
TesteSend123 enviado na porta 8.
Erro ao enviar.
Erro ao enviar.
Status do Send: 0
+EVT:SEND_CONFIRMED_OK
```

A mensagem de confirmação `+EVT:SEND_CONFIRMED_OK` define que o envio da mensagem foi bem-sucedido.

<br><hr><br>

### GetDeviceEUI()
Retorna o Device EUI do dispositivo.

```cs
GetDeviceEUI();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando Device EUI do dispositivo.
    Serial.println(abp.GetDeviceEUI());
}

void loop()
{

}
```

**Saída no monitor serial:**

```
AC1F09FFFE090B61
```

<br><hr><br>

### SetDeviceEUI()
Define o Device EUI do dispositivo à partir de uma sequência hexadecimal de 16 caracteres.

```cs
SetDeviceEUI(string deviceEui);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Definindo Device EUI.
    abp.SetDeviceEUI("AC1F09FFFE12AFD6");
}

void loop()
{

}
```

<br><hr><br>

### GetAppskey()
Retorna a chave Appskey do dispositivo.

```cs
GetAppskey();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando Appskey do dispositivo.
    Serial.println(abp.GetAppskey());
}

void loop()
{

}
```

**Saída no monitor serial:**

```
65a582aa8221aab2a77ece366c5dd0c9
```

<br><hr><br>

### GetNwkskey()
Retorna a chave NwkSKey do dispositivo.

```cs
GetNwkskey();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando Nwkskey do dispositivo.
    Serial.println(abp.GetNwkskey());
}

void loop()
{

}
```

**Saída no monitor serial:**

```
d836a90efb0116c8543686c3df2e738a
```

<br><hr><br>

### GetDeviceAddress()
Retorna o Device Address do dispositivo.

```cs
GetDeviceAddress();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando Device Address do dispositivo.
    Serial.println(abp.GetDeviceAddress());
}

void loop()
{

}
```

**Saída no monitor serial:**

```
021505ef
```

<br><hr><br>

### GetJoinMode()
Retorna o modo de operação do dispositivo conectado (ABP ou OTAA).

```cs
GetJoinMode();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando modo de operação.
    Serial.println(abp.GetJoinMode());
}

void loop()
{

}
```

**Saída no monitor serial:**
```
ABP
```

<br><hr><br>

### GetNetworkJoinStatus()
Retorna se a instância de conexão está conectada ou não (0 = Não Conectado, 1 = Conectado).

```cs
GetNetworkJoinStatus();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando status atual da conexão.
    Serial.println(abp.GetNetworkJoinStatus());
}

void loop()
{

}
```

**Saída no monitor serial:**
```
1
```

<br><hr><br>

### GetConfirmMode()
Retorna se o modo de confirmação está ativado ou não (0 = Desabilitado, 1 = Habilitado).

```cs
GetConfirmMode();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando modo de confirmação.
    Serial.println(abp.GetConfirmMode());
}

void loop()
{

}
```

**Saída no monitor serial:**
```
0
```

<br><hr><br>

### SetConfirmMode()
Habilita ou desabilita o modo de confirmação de envio de informações pelo `SendData()` (0 = Desabilita, 1 = Habilita).

```cs
SetConfirmMode(bool mode);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Definindo modo de confirmação
    abp.SetConfirmMode(1);
}

void loop()
{

}
```

Definindo o modo de confirmação, é possível definir também o número de tentativas de envio de informações usando `SendData()`, através do método `SetNumberOfRetransmissions()`.

<br><hr><br>

### GetNumberOfRetransmissions()
Retorna o número de tentativas de mensagem definidos para o comando `SendData()`.

```cs
GetNumberOfRetransmissions();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando número de tentativas do SendData().
    Serial.println(abp.GetNumberOfRetransmissions());
}

void loop()
{

}
```

**Saída no monitor serial:**

```
7
```

<br><hr><br>

### SetNumberOfRetransmissions()
Define o número de tentativas de envio de informação usando `SendData()`.

```cs
SetNumberOfRetransmissions(int val);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Definindo número de tentativas do SendData().
    abp.SetNumberOfRetransmissions(7);

}

void loop()
{

}
```

<br><hr><br>

### GetActiveRegion()
Retorna o valor correspondente a frequência de banda configurada no dispositivo.

Cada região é definida por um valor diferente.

| Região        | Retorno       |
| :-----------  | :-----------: |
| EU433         | 0             |
| CN470         | 1             |
| RU864         | 2             |
| IN865         | 3             |
| EU868         | 4             |
| US915         | 5             |
| AU915         | 6             |
| KR920         | 7             |
| AS923-1       | 8             |
| AS923-2       | 9             |
| AS923-3       | 10            |
| AS923-4       | 11            |

A configuração padrão de banda definida nas conexões é `AU915`.

```cs
GetActiveRegion();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando região ativa.
    Serial.println(abp.GetActiveRegion());

}

void loop()
{

}
```

**Saída no monitor serial:**
```
6
```

<br><hr><br>

### SetActiveRegion()
Define a configuração de banda do dispositivo.

```cs
SetActiveRegion(int bandRegion);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Definindo região ativa.
    abp.SetActiveRegion(4);

}

void loop()
{

}
```

<br><hr><br>

### GetClass()
Retorna a classe de operação definida no dispositivo (A, B ou C).

```
GetClass();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Retornando classe de operação.
    Serial.println(abp.GetClass());

}

void loop()
{

}
```

<br><hr><br>

### SetClass()
Define a classe de operação do dispositivo (A, B ou C).

```cs
SetClass(char classMode);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("021505ef", "65a582aa8221aab2a77ece366c5dd0c9", "d836a90efb0116c8543686c3df2e738a", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(3000);

    Serial.begin(115200);
    abp.Setup();

    //Definindo classe de operação.
    abp.SetClass('B');

}

void loop()
{

}
```

<br><hr><br>

### GetBatteryLevel()
Retorna o nível de bateria atual do dispositivo.

```cs
GetBatteryLevel();
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    Serial.begin(115200);
    abp.Setup();
}

void loop()
{
    delay(5000);

    //Retorna o nível de bateria atual do dispositivo.
    Serial.println(abp.GetBatteryLevel());
}
```

**Saída no monitor serial:**

```
4.19
```

<br><hr><br>

### SleepAll()
Habilita o modo sleep do dispositivo e todos seus componentes durante um período de tempo (em milissegundos).

Quando o parâmetro de tempo de sleep `time` não é informado, o dispositivo entra em modo sleep por tempo inderteminado.

```cs
SleepAll(int time);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);

    Serial.begin(115200);
    abp.Setup();
}

void loop()
{
    Serial.println("Entrando no modo sleep por 5 segundos...");

    //Habilita modo sleep por 5 segundos
    abp.SleepAll(5000);

    Serial.println("Fim do modo sleep.");

    delay(2000);
}
```

<br><hr><br>

### SleepCPU()
Habilita o modo sleep do CPU do dispositivo durante um período de tempo (em milissegundos).

Quando o parâmetro de tempo de sleep `time` não é informado, o dispositivo entra em modo sleep por tempo inderteminado.

```cs
SleepCPU(int time);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);

    Serial.begin(115200);
    abp.Setup();
}

void loop()
{
    Serial.println("Entrando no modo sleep por 5 segundos...");

    //Habilita modo sleep por 5 segundos
    abp.SleepCPU(5000);

    Serial.println("Fim do modo sleep.");

    delay(2000);
}
```

<br><hr><br>

### SleepLoRa()
Habilita o modo sleep do dispositivo LoRa durante um período de tempo (em milissegundos).

```cs
SleepLoRa(int time);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);

    Serial.begin(115200);
    abp.Setup();
}

void loop()
{
    Serial.println("Entrando no modo sleep por 5 segundos...");

    //Habilita modo sleep por 5 segundos
    abp.SleepLoRa(5000);

    Serial.println("Fim do modo sleep.");

    delay(2000);
}
```

<br><hr><br>

### SetChannelMask()
Configura a máscara de canal (channel mask) do dispositivo.

O channel mask permite que os erros de confirmação ou de envio das transmissões via uplink sejam eliminadas ou pelo menos otimizadas.

```cs
SetChannelMask(uint16_t mask);
```

**Exemplo:**

```cpp
#include "DeviceLoraABP.h"
#include "DeviceLoraOTAA.h"

DeviceLoraABP abp("02c27d69", "164d904dd7688c5b6649805b818d4c37", "a31dbce5ee57af45dfccb2f63a8a72ba", "AC1F09FFFE090B61", 'C', 0x0001);

void setup()
{
    delay(5000);

    Serial.begin(115200);
    abp.Setup();
}

void loop()
{
    delay(2000);

    //Habilitando outro valor para o channel mask
    abp.SetChannelMask(0x0010);
}
```

Por padrão, a máscara de canal definida nos dispositivos é ``0x00FF``, o que significa que, durante as transmissões de uplink o dispositivo vai tentar definir o channel mask automaticamente. Isso pode ocasionar em erros de confirmação/de transmissão da mensagem, mesmo que o modo de confirmação e número de tentativas estejam habilitados e configurados corretamente.

Para a configuração de banda `AU915`, podemos definir esse valor inicialmente, na instância de conexão, como `0x0001`.