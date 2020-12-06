## Сборка
```
autoreconf -fisv && ./configure && make
```
После configure .c и .h файлы содержат строку с комментарием
## Вывод первых строк .c и .h файлов
```
make head
```
## Обновление комментария в .c и .h файлах
```
make update_comment
```