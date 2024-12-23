# Рассчетная работа 
В моем варианте рассчетной работы нужно было найти количество хорд в неориентированном графе.
 Хорда в графе - ребро, соединяющее две вершины цикла, но не являющееся его частью.
 
![](image-1.png)

Чтобы найти все хорды в графе нужно найти все циклы.

Для поиска циклов я использовала поиск в глубину. При обходе в глубину вершина помечается как посещенная и цикл идет дальше в вершину, еще не посещенную.
Если из вершины нет возможных путей - поиск возвращается в вершину-родитель текущей.

Мой граф задан матрицей инцидентности

![](image.png)

Я путем многократного обхода в глубину нашла все циклы, потом в цикле находила графы.

![](1.png)

Циклы выводятся в столбик и после чего подсчитывается количество хорд в графе

# Вывод

В процессе выполнения рассчетной работы я познакомилась с такой структурой данных как графы, научилась работать с алгоритмом поиска в глубину и решила поставленную задачу.
