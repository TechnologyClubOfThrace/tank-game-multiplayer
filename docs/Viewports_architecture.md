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
H ομαδοποίηση των entities γίνεται με τη χρήση ενώς αναγνωριστικού viewport id. Συγκεκριμένα κάποιο entity μπορεί να ανήκη σε περισσότερα από ένα viewport id.
Μία τετοια περίπτωση είναι το τανκ και το turret που πρέπει να εμφανίζονται τόσο στην κύρια πίστα, όσο και στο radar view port.
Με την χρήση της αρχιτεκτονικής βάση viewports, δεν χρειάζεται να γίνεται ταξινόμιση των entities βάση κάποιας μεταβλητής z-order,
όπου θα απαιτούνταν να γίνεται ταξινόμιση της λίστας των entities, όποτε γινόταν προσθήκη νέου entity.

table markdown using https://www.tablesgenerator.com/markdown_tables

| Entity                    | Κάτω από                                                                             | Πάνω από                                                          | Θέση στο entires array                               | Viewport id                 |
|---------------------------|--------------------------------------------------------------------------------------|-------------------------------------------------------------------|------------------------------------------------------|-----------------------------|
| Level Background [LB] (0) | every other entity                                                                   |                                                                   | 0-LB_count                                           | 0 [default]                 |
| Player tank               | turret, tank explosion,  wall cover,  radar                                          | LB,  Tank trace                                                   |                                                      | 1                           |
| Turret                    | tank explosion,  radar                                                               | LB,  parent Player tank,  tank trace,  wall cover                 |                                                      | 3                           |
| Tank trace                | Player tank,  turret,  tank bomb,  health-ammo,  tank explosion, wall cover,   radar | LB,  older tank trace                                             | after LB_count, after older tank trace               |  0                          |
| Tank bomb                 | radar                                                                                | LB,  tank trace,  health-ammo                                     | after LB_count,  after tank trace, after health-ammo | 3 or (2 if health-ammo = 1) |
| Health-ammo               | tank bomb,  tank explosion,  radar                                                   | LB,  tank trace                                                   |                                                      | 2 or 1                      |
| Tank explosion            | radar                                                                                | LB,  player tank,  turret,  tank trace,  health-ammo,  wall cover |                                                      | 4                           |
| Wall cover                | turret,  tank explosion,  radar                                                      | LB,  player tank,  tank trace                                     |                                                      | 2                           |
| Radar                     |                                                                                      | every other entity                                                |                                                      | 5                           |
