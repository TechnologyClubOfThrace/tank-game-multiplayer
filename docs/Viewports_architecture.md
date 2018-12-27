# Viewports architecture

Τα viewports χρησιμοποιούνται για την ομαδοποίηση και απεικόνιση των entities. Στο game engine υπάρχει πάντα το default viewport με id=0. Η ομαδοποίηση είναι απαραίτητη για να εμφανίζονται τα entites του παιχνιδιού καθώς το render γίνετε ένα ένα για κάθε entity. Αν για παράδειγμα κανουμε render πρώτα το τανκ και στη συνέχεια το background της πίστας, τότε το τανκ δεν θα εμφανιστεί ποτέ στην οθόνη γιατί το background θα έχει εμφανιστεί από επάνω.

# Παράδειγμα χρήσης 1
Θέλουμε στο παιχνίδι να εμφανίσουμε τα ακόλουθα entities:
- το background της πίστας
- τα tank των παικτών
- tank turret
- τα ίχνη των τανκ
- τα βλήματα που εκτοξευουν τα τανκ
- τα αντικείμενα που αφήνει το τανκ οταν χάνει (health, ammo)
- την έκρηξη του τανκ οταν καταστρέφεται
- τα τείχη που εμφανίζονται τυχαία μέσα στην πίστα για να κρύβονται τα τανκ
- το radar που δίχνει την θέση του τανκ στην πιστα

Ομαδοποίηση entities
- Το background της πίστας εμφανίζεται πάντα πίσω από όλα τα άλλα entities, οπότε θα μπεί στην αρχή του entites array με viewport id=0
- τα τανκ των παικτών εμφανίζονται πάντα πάνω απο το background της πίστας

table markdown using https://www.tablesgenerator.com/markdown_tables

| Entity                    | Κάτω από                                                                             | Πάνω από                                                          | Θέση στο entires array                               | Viewport id                                    |
|---------------------------|--------------------------------------------------------------------------------------|-------------------------------------------------------------------|------------------------------------------------------|------------------------------------------------|
| Level Background [LB] (0) | every other entity                                                                   |                                                                   | 0-LB_count                                           | 0 [default]                                    |
| Player tank               | turret, tank explosion,  wall cover,  radar                                          | LB,  Tank trace                                                   | after LB_count                                       | 1                                              |
| Turret                    | tank explosion,  radar                                                               | LB,  parent Player tank,  tank trace,  wall cover                 | after LB_count                                       | 3                                              |
| Tank trace                | Player tank,  turret,  tank bomb,  health-ammo,  tank explosion, wall cover,   radar | LB,  older tank trace                                             | after LB_count, after older tank trace               |  0, under health-ammo,  under older tank trace |
| Tank bomb                 | radar                                                                                | LB,  tank trace,  health-ammo                                     | after LB_count,  after tank trace, after health-ammo | 3 or (2 if health-ammo = 1)                    |
| Health-ammo               | tank bomb,  tank explosion,  radar                                                   | LB,  tank trace                                                   |                                                      | 2 or 1                                         |
| Tank explosion            | radar                                                                                | LB,  player tank,  turret,  tank trace,  health-ammo,  wall cover |                                                      | 4                                              |
| Wall cover                | turret,  tank explosion,  radar                                                      | LB,  player tank,  tank trace                                     |                                                      | 2                                              |
| Radar                     |                                                                                      | every other entity                                                |                                                      | 5                                              |