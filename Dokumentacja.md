Antoni Siółko

Maksym Shvets

Dokumentacja

Gra: Monkey Jump

1. Wybieranie tematu:
   Po rozpoczęciu projektu od razu padło kilka pomysłów na temat popularnych gier telefonicznych takich jak Tetris, 2048, coś w stylu „Need for Speed” oraz jakaś 3d gra w labiryncie. W końcu doszliśmy do wniosku, że byłoby ciekawie poeksperymentować z grą „Monkey Jump”, ale, która polega na tym, małpa rusza się w górę w nieskończoność skacząc na platformach. Dla początku skorzystaliśmy z tutorialu, w którym funkcjonalność kodu była maksymalnie prosta, ale w niektórych miejscach pusta, co musieliśmy dodać dla pełnego funkcjonowania naszej gry. Też dodaliśmy monstra którego trzeba starać się ominąć, a jeżeli się da to można na niego trafić z góry i dostać dodatkowe punkty. Jeżeli spotkacie się w innym miejscu, niestety, musicie zacząć grę ponownie.

Wykorzystywana biblioteka:
Na początku chcieliśmy użyć omawianej na ćwiczeniu biblioteki „Allegro 5”, ale znaleźliśmy bardziej rozpowszechnioną opcję, które jest używana w wielu projektach. Jest to biblioteka SFML(*Simple and Fast Multimedia Liberary*). Poniżej zamieszczamy krótki tutorial, jak ta biblioteka musi się dołączać do Visual Studio (używaliśmy go do napisania kodu więc polecamy najpierw go pobrać w wersji Community, też do tego jest link - <https://visualstudio.microsoft.com/vs/> )









1. Tutorial

Wejdź na stronę <https://www.sfml-dev.org/download/sfml/2.5.1/> i pobierz wersję odpowiadającą twojemu VS. Jeśli używasz programu Visual Studio 2015 lub nowszego, możesz śmiało użyć wersji SFML skompilowanej dla Visual C++ 15 (VS 2017), która jest nadal kompatybilna z nowszymi wersjami zestawu narzędzi.

![sfml](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/59a6402d-b332-4c78-8413-9bdf51a1c0ac)

Wypakuj w dowolnym miejscu folder SFML. Otwórz projekt w Visual Studio.

![1](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/ebde9ac5-0dc8-453d-9805-27532f8ae0e7)


Kliknij prawym przyciskiem myszy na swoją aplikację i wybierz właściwości.

![2](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/a6ed15c0-5752-4d23-9056-5068310d88e7)


Otwórz zakładkę C/C++ i wybierz Dodatkowe katalogi plików nagłówkowych

![3](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/78f77816-51b3-4aca-9634-08c6d78fe9db)


Wybierz edytuj

![4](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/bbdf34b0-d44d-4d71-b6b1-e3a39e6777d8)


Następnie wklej ścieżkę folderu “include” z wypakowanego SFML

![5](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/ee9bd621-1290-47d7-8add-b34b86c577f3)


Wzakładce Preprocesor edytuj pole “Definicje preprocesora”

![6](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/379bfe46-206d-4765-ad69-dfa60d4db71f)


W wyznaczonym polu należy dopisać: SFML\_STATIC

![7](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/fdbb12fa-28ee-4734-a427-e28ed3527628)


Teraz otwieramy zakładkę Konsolidator, a w niej Ogólne i wyszukujemy Dodatkowe katalogi biblioteki.

![8](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/8897aa3c-44f3-40aa-9652-0fadd478e1ad)


W wyznaczonym polu wklejamy ścieżkę do folderu lib z wypakowanego SFML

![9](https://github.com/maksimus209/mokey-project-wdp/assets/135655103/2f9bfa6f-835b-4eaf-9f32-a601ed087958)


Następnie otwieramy zakładkę Dane Wejściowe w Konsolidatorze

Wklejamy w polu Dodatkowe zależności następujące rzeczy:

sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-system-s-d.lib sfml-main-d.lib opengl32.lib freetype.lib winmm.lib gdi32.lib

Kolejność, która została podana ma znaczenie.

To wszystko. Teraz możemy zacząć grać. Miłej zabawy!

Jeżeli tutorial ten nie jest zrozumiały lub nie wystarcza wizualnej treści możecie obejrzeć wideo na YouTube, które nam pomogło prawidłowo załadować wszystkie pliki. Poniżej zostawiam link:
<https://www.youtube.com/watch?v=VWWSc2nqrEA&t=171s&ab_channel=Zipped>




3\. Zasada gry:
Gra polega na kontrolowaniu małpy, która skacze po platformach w górę, celem zdobycia jak najlepszego wyniku końcowego. W trakcie gry możemy napotkać na węża, który będzie nam przeszkadzał w osiąganiu wysokiego wyniku. Możemy go ominąć bez zdobywania dodatkowych punktów i unikając śmierci ale można go brutalnie pokonać jak w Super Mario – trafiwszy go w głowę. Kierowanie naszą małpą jest proste – posługujemy się tylko dwoma przyciskami na klawiaturze: key RIGHT i key LEFT. Wiedząc wszystkie zasady możecie przystąpić do gry.


