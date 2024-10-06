# NFC based radio for kids

Uses a ESP32 A1S + PN532 NFC reader to mimic and old-school walkman

<img src="https://github.com/user-attachments/assets/a9f5c5d3-2e27-4fe0-b451-c024aa19bd1c" width="500">
<br/>
<img src="https://github.com/user-attachments/assets/28908ec0-2d63-413b-8d3d-23cb4a0d11ae" width="500">

# BOM

* ESP32 A1S ES8388 v2.2: https://es.aliexpress.com/item/4000130915903.html?spm=a2g0o.order_list.order_list_main.28.4f82194dt8NG1n&gatewayAdapt=glo2esp
* 3W 4ohm speakers (x2): https://es.aliexpress.com/item/1005006144805292.html?spm=a2g0o.order_list.order_list_main.33.4f82194dt8NG1n&gatewayAdapt=glo2esp
* PN532: https://es.aliexpress.com/item/1005007154965417.html?spm=a2g0o.order_list.order_list_main.38.4f82194dt8NG1n&gatewayAdapt=glo2esp
* M3 screws (6mm, 8mm, best to order the mix): https://es.aliexpress.com/item/32794842281.html?spm=a2g0o.order_list.order_list_main.478.17f0194dBYZLen&gatewayAdapt=glo2esp
* M3 brass inserts (M3-OD 4.5, 3mm): https://es.aliexpress.com/item/1005003582355741.html?spm=a2g0o.order_list.order_list_main.158.17f0194dBYZLen&gatewayAdapt=glo2esp
* 4x2 magnet: https://es.aliexpress.com/item/1005003639279792.html?spm=a2g0o.productlist.main.1.69592af9iuftWd&algo_pvid=7d5d6dca-b5f2-4312-8390-0971dc685602&algo_exp_id=7d5d6dca-b5f2-4312-8390-0971dc685602-0&pdp_npi=4%40dis%21EUR%212.13%212.03%21%21%212.29%212.18%21%40211b876717282148957681292e5c25%2112000027816721427%21sea%21ES%21137979760%21X&curPageLogUid=KVqdLuzkaS3D&utparam-url=scene%3Asearch%7Cquery_from%3A
* 6x3 magnet: https://es.aliexpress.com/item/1005006291065081.html?spm=a2g0o.productlist.main.1.5e7e7f14mJmUiZ&algo_pvid=ea6b8d94-e00b-46b7-b66e-b1be89cbc0d0&algo_exp_id=ea6b8d94-e00b-46b7-b66e-b1be89cbc0d0-0&pdp_npi=4%40dis%21EUR%215.81%212.79%21%21%2144.15%2121.20%21%40211b6a7a17282174849856536e1031%2112000036632421438%21sea%21ES%21137979760%21X&curPageLogUid=OLsJFOsyTCpJ&utparam-url=scene%3Asearch%7Cquery_from%3A
* 20mm L x 5mm OD spring (x10): https://es.aliexpress.com/item/1005005312536098.html?spm=a2g0o.productlist.main.1.438575ebR21h0U&algo_pvid=c385ab69-7aa9-4e0a-929b-e97faa380a16&algo_exp_id=c385ab69-7aa9-4e0a-929b-e97faa380a16-0&pdp_npi=4%40dis%21EUR%213.12%212.95%21%21%2123.69%2122.37%21%40211b617a17282175473502166e50a1%2112000032590665845%21sea%21ES%21137979760%21X&curPageLogUid=D9e1ubeB5BbD&utparam-url=scene%3Asearch%7Cquery_from%3A
* 12mm latching Switch: https://es.aliexpress.com/item/1005004474876388.html?spm=a2g0o.productlist.main.45.72876186DJfgCl&algo_pvid=409fb821-347b-4a3d-9398-ab32eea84b01&algo_exp_id=409fb821-347b-4a3d-9398-ab32eea84b01-22&pdp_npi=4%40dis%21EUR%212.64%212.50%21%21%212.84%212.69%21%40211b617b17282176419012833e1100%2112000029293339568%21sea%21ES%21137979760%21X&curPageLogUid=oQG5pdMuBWuk&utparam-url=scene%3Asearch%7Cquery_from%3A
* NFC tags: https://es.aliexpress.com/item/1005005872961523.html?spm=a2g0o.productlist.main.3.1d6d1f78mzObVT&algo_pvid=7d78db2c-3b29-4714-b27a-a28eeabdb076&algo_exp_id=7d78db2c-3b29-4714-b27a-a28eeabdb076-1&pdp_npi=4%40dis%21EUR%2110.10%214.75%21%21%2176.71%2136.05%21%40210384cc17282184499365167e473e%2112000034654498837%21sea%21ES%21137979760%21X&curPageLogUid=4299ztlWQ0eG&utparam-url=scene%3Asearch%7Cquery_from%3A
