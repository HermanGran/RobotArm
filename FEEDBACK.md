# Feedback Gruppe12 - Seriell kinematisk lenke

`M_PI` er platformavhening. Finnes bl.a ikke på MSVC. 
Bruk threepp sin `math::PI`.

Threepp har også fasiliteter for å konvertere mellom radians og degrees.

```cpp
 Segment::Segment(const Vector3 &startPoint_, float len_, float angle_, const Color &color_) {
    startPoint = startPoint_;
    len = len_;
    angle = degreesToRadians(angle_);
    segmentColor = color_;

    ...
}
```
Her har du underscore på parameter og ikke på felt. Vanligvis er det omvendt..
Bruk også alltid member initialzer list der dette er mulig.


```cpp
void Segment::updateGeometry() {
    float dx = len * cos(this->angle);
    float dy = len * sin(this->angle);
    endPoint.set(startPoint.x + dx, startPoint.y + dy, startPoint.z);
//    geometry->setFromPoints({startPoint, endPoint});
    line->rotation.z = angle; // <---
 }
```
Over har jeg kommentert ut at du oppdaterer geomentrien på segmentet ditt. 
Endre heller rotasjonsvinkelen. Om det skal være snakk om Invers kinematikk så vil 
du ha en rekke ledd og du har kun lov å rotere eller translere disse. Tenk på en fysisk robot. 
Du kan ikke endre den geometriske konstruksjonen. API'et er nok heller ikke teknisk sett tenkt brukt på denne måten.

Du trenger en klasse `Segments` eller lignende som gjenspeiler at du har en rekke segments som jobber sammen. 
Du har ikke individuelle segmenter, men en gruppe segmenter som jobber mot et felles mål. 
En egen klasse trengs for å synkronisere dette.

Videre kan du dra litt inspirisjon [herifra](https://markaren.github.io/WebGL-demos/) om hvordan du kan 
representere generiske kinematisk lenker.

Du fikk en kommentar i timen om at du kan tenke på å bruke Arv ved å lage et abstract interface `IKSolver`, ala:

```cpp
class IKSolver {
    
public:
    virtual std::vector<float> solve(const DATASTRUKTUR& kine, const Vector3& pos);
};
```
Der `DATASTRUKTUR` innholder den kinematiske lenken din.

Da kan du implementere ulike typer solvere som geometrisk og Cyclic Coordinate Decent, og la bruker velge hvilken som skal brukes. 
Om du er glad i matte kan du se på f.eks metoder som [Damped Least Squared](https://mathweb.ucsd.edu/~sbuss/ResearchWeb/ikmethods/SdlsPaper.pdf), 
men da trenger du et bibliotek som Eigen.

`/src/Example` burde ligge i en egen folder `/examples` i rotfolderen din.

---
Tilbakemeldingen kan inneholde feil og mangler. Ta kontak ved spørsmål.
