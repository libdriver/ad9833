[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver AD9833

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ad9833/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

AD9833 は、正弦波、三角波、方形波出力を生成できる低電力のプログラマブル波形発生器です。 波形生成は、さまざまなタイプのセンシング、作動、およびタイムドメイン反射率測定 (TDR) アプリケーションで必要となります。 出力周波数と位相はソフトウェアでプログラム可能なため、簡単に調整できます。 外部コンポーネントは必要ありません。 周波数レジスタは 28 ビット幅です。25 MHz のクロック レートでは、0.1 Hz の分解能を実現できます。 1 MHz のクロックレートで、AD9833 は 0.004 Hz の分解能に調整できます。 AD9833 への書き込みは 3 線式シリアル インターフェイス経由で行われます。 このシリアル インターフェイスは最大 40 MHz のクロック レートで動作し、DSP およびマイクロコントローラ標準と互換性があります。 このデバイスは 2.3 V ～ 5.5 V の電源で動作します。AD9833 にはパワーダウン機能 (SLEEP) があります。 この機能により、使用されていないデバイスのセクションの電源がオフになり、部品の電流消費が最小限に抑えられます。 たとえば、クロック出力の生成中に DAC の電源をオフにすることができます。

LibDriver AD9833 は、LibDriver によって起動された AD9833 のフル機能ドライバです。直接デジタル周波数合成 (DDS) 出力機能とその他の機能を提供します。 LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver AD9833のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver AD9833用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver AD9833ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver AD9833プログラミング例が含まれています。

/ docディレクトリには、LibDriver AD9833オフラインドキュメントが含まれています。

/ datasheetディレクトリには、AD9833データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

#### example basic

```C
#include "driver_ad9833_basic.h"

uint8_t res;

/* init */
res = ad9833_basic_init();
if (res != 0)
{
    return 1;
}

...
    
/* set number */
res = ad9833_basic_set_used_register(AD9833_NUMBER_0);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

/* set freq */
res = ad9833_basic_set_frequency(AD9833_NUMBER_0, 10 * 1000);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

...
    
/* set phase */
res = ad9833_basic_set_phase(number, 3.14159265357 / 2);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

...
    
/* set output mode */
res = ad9833_basic_set_output_mode(AD9833_OUTPUT_MODE_SIN);
if (res != 0)
{
    (void)ad9833_basic_deinit();
    
    return 1;
}

...

/* deinit */
(void)ad9833_basic_deinit();

return 0;
```

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ad9833/index.html](https://www.libdriver.com/docs/ad9833/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。