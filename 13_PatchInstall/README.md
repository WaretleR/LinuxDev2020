## Сборка и установка в произвольный каталог
```
autoreconf -fisv && ./configure --prefix=<каталог>
sudo make install
```
## Сборка по стандартной схеме и установка в произвольный каталог
```
autoreconf -fisv && ./configure --prefix=/usr
sudo make install DESTDIR=<каталог>
```
Варианты ответов на вопросы программы: да (yes) / нет (no).