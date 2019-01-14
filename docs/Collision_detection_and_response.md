# ****Collision detection rules****

Οι έλεγχοι που πρέπει να γίνονται για collision εξαρτώνται από το entity και θα καλούνται μέσα από το physics system, καθώς από εκεί μεταβάλεται το transform του κάθε entity.

Το τανκ ελέγχει για collision:
- Άλλα tank
- level background walls
- Wall cover
- Health / ammo etc

Οι σφαίρες ελέγχουν για collision:
- τανκ
- level background walls
- Wall cover

|   | Ελέγχει  | Ελέγχεται |
| ------------ | ------------ | ------------ |
| Τανκ  | x  | x  |
| LB walls  |   | x |
| Wall cover  |   | x |
| Health  |   | x |
| Bullet  | x |   |


