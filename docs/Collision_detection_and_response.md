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

Ο αλγόριθμος εξέτασης των collisions θα πρέπει να εκτελείται μόνο για τα entities που έχουν σήμανση ώς ελεγκτές. Στην περίπτωση που το entity έχει την δυνατότητα να ελέγχει και να ελέγχεται για collisions (tank) θα πρέπει ο αλγόριθμος να ελέγχει οτι δεν γίνεται έλεγχος του entity με τον εαυτό του.

**Πίνακας των entities με δυνατότητα "Ελέγχει" ή "Ελέγχεται"**

|   | Ελέγχει  | Ελέγχεται |
| ------------ | ------------ | ------------ |
| Τανκ  | x  | x  |
| LB walls  |   | x |
| Wall cover  |   | x |
| Health  |   | x |
| Bullet  | x |   |


**Τύποι των colliders**
Το entity μπορεί να περιέχει μία συλλογή από οποιοδήποτε από τους παρακάτω colliders:
- PointCollider2D
- RectangleCollider2D
- ConvexPolygonCollider2D

**Πίνακας των colliders που περιέχουν τα entities**

|   | PointCollider2D  | RectangleCollider2D | ConvexPolygonCollider2D |
| ------------ | ------------ | ------------ | ------------ |
| Τανκ  |  |  | x |
| LB walls  |   | x |  |
| Wall cover  |   |  | x |
| Health  |   | x |  |
| Bullet  | x |   |  |

**Collider transformations**
Ειδικά τα entities που κινούνται πρέπει μετά από την κίνησή τους από το physics engine, να εφαρμόζουν τα ανάλογα transformations και στους colliders που περιέχουν. **Σε αυτή την κατηγορία ανήκουν δύο entities, τα τανκ και τα bullet.** Τα υπόλοιπα entities έχουν στατικούς colliders.

**Collider Response**
Τα δύο colliders (tank, bullet) που έχουν την δυνατότητα ελέγχου για collisions με άλλα entities, μετά το collision θα πρέπει να δώσουν μία "απάντηση" ώς προς το τί θα γίνει. Αυτό ορίζεται από το ColliderResponse enum.

**ColliderResponse Enum**
| Remove | Should remove the entity from the collection  |
| XCollision  |  Should revert the position.x and rotation to its previous value |
| YCollision  |  Should revert the position.y and rotation to its previous value |
| XYCollision  |  Should revert the position x, y and rotation to its previous value |

- Οταν bullet συγκρουστεί με οποιοδήποτε άλλο collider
