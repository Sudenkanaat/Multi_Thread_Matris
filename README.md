Versiyon 1:

Bu kod, çoklu threadler kullanarak iki matrisin çarpımını hesaplar. Thread, her biri matrisin belirli bir satırını hesaplamak için çalışır. Thread arasında senkronizasyon ve veri paylaşımı, mutex'ler ve koşul değişkenleri kullanılarak gerçekleştirilir.
matrisHesapla fonksiyonu, thread olarak çalıştırılan fonksiyondur. Thread, satır numarasını alır ve o satırın çarpımını hesaplar. Eğer henüz tüm threadler yaratılmamışsa, thread bekleme moduna geçer. Tüm threadler yaratıldıysa, bekleyen threadleri uyandırmak için koşul değişkeni kullanılır. 
Thread, sharedMatrisA ve sharedMatrisB vektörlerini kullanarak çarpımı hesaplar ve sonuçları sharedMatrisC vektörüne yazar. Thread sonlandırılır.
Ana program, pthread_create fonksiyonunu kullanarak threadleri oluşturur.
Threadler yaratıldıktan sonra, diğer bekleyen threadlerin devam etmesi için koşul değişkeni kullanılır.
Tüm threadler tamamlanana kadar ana program bekler.
Sonuçlar, dosyayaYaz fonksiyonu aracılığıyla ilgili dosyalara yazılır.
Bu kodun amacı, verilen matris boyutlarına göre matrisA ve matrisB matrislerini oluşturmak, çarpımı hesaplamak ve sonucu matrisC dosyasına yazmaktır. Ayrıca, rastgeleSayilar dosyasına da rastgele sayılar yazılmaktadır. 

Versiyon 2:
Bu kod, kullanıcıdan alınan m, n ve k değerlerine göre rastgele matrisler oluşturmak ve bu matrisleri ayrı ayrı dosyalara yazmaktır. Kullanıcı tarafından belirlenen boyutlara sahip rastgele matrisler oluşturulur ve bu matrisler ayrı ayrı dosyalara yazılır. 
Amaç, versiyon 1 kullanarak threadlerin daha hızlı sonuç aldığını göstermektir.
