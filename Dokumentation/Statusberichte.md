# Statusberichte

# 31 Januar 2022

### Rollenverteilung:
- Abenet: Scrum Master, Development, Testing
- Chloe: Development, Testing, "Rechtschreibpolizei"
- Nils: Development, Product Owner, Testing
- Hanna: Art Director, Development, Testing

### Status:
- Spielidee festgelegt (Terraria-Clone)
- Entwicklungsumgebungen für alle eingerichtet (Linux, Mac und Windows)
- Umsetzungsplan erstellt (Programmiersprache C++, Werkzeuge,...)
- Agiles Board mit Features auf Trello

### Gemachte Erfahrungen:
- unterschiedliche Ideen/Wünsche/Erwartungen müssen vereint werden (kann manchmal schwierig sein)
- Einrichten der Entwicklungsumgebungen bei Mac kompliziert 


# 24 Februar 2022

### Fortschritt:
- Das Laden von Objekten und Blöcken ist möglich.
- Das Erstellen von Objekten mit verschiedenen KI-Typen ist möglich (Player, NPC, Enemy), alle werden generalisiert über den Objectmanager abgearbeitet.
- Die Welt kann mit unterschiedlichen Varianten des "Perlin Noise" generiert werden und das potenziell unendlich (wir haben aber die Welt künstlich beschränkt, obwohl unser Speichermanagement darauf optimiert ist, unendlich große Welten verarbeiten zu können, ohne Performanceeinbußen)
- Die Welt kann erstellt, bearbeitet (sowohl Zugriff auf Blöcke der einzelen Chunks, als auch das Plazieren von Blöcken ist möglich) und geladen werden.
- Der Player existiert und ist grundlegend voll funktionsfähig.
- Der Renderer ist darauf optimiert, dass für alle Objekte ein Grafikkartencall und für jeden Chunk jeweils auch ein Grafikkartencall benötigt wird (sehr gute Performance garantiert)
- Die grundlegende stand-alone Engine ist vollständig für unseren Terrariaklon bis auf den Collisionmanager, der weitgehend fertig ist. Außerdem ist sie Plattformunabhängig.

### Risikobetrachtung:
- Wir sind aktuell optimal im Zeitplan.
- Aufgrund unseres Team knowledges und der funktionierenden Arbeitsteilung (Architektur, Programmierung, Softwareengineering, Design, Bürokratie) ist der einzige Risikofaktor, der den Abschluss aktuell gefährden könnte, die Zeitverfügberkeit.

### Gemachte Erfahrungen:
- Terminmanagement "schwierig".
- Arbeitsteilung funktioniert gut

### Programmanleitung:
- BlockID selektieren: Mausrad klicken
- Selektierte BlockID plazieren: Linksklick
- Objekte spawnen: Rechtsklick
- Bewegung: W,A,S,D
- Zoomen: R,T
- Reset Zoom: E
