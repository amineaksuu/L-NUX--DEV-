# LINUX ODEVI
C dili ile oluşturulmuştur. 
Özellikler: Syslog dosyasını satır satır okur. Her satırı bağlı listeye bir düğüm olarak ekler. Tüm günlükleri ekrana yazdırır. Program tamamlandıktan sonra bellek temizliği yapar.
Gereksinimler: Bir Linux dağıtımı (Ubuntu, Debian, vs.) ,GCC derleyicisi, Syslog dosyasına erişim izni (Root yetkisi gerekebilir).
Kodda tek yönlü (singly linked list) bağlı liste kullanılmıştır. Her düğüm (GunlukKaydi yapısı), bir günlük mesajı saklar ve bir sonraki düğüme işaret eden bir gösterici (sonraki) içerir. Listenin sonunda NULL değeri bulunur, yani çift yönlü veya dairesel bir yapı kullanılmamıştır.
