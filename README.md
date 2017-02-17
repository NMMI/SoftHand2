qbmove_firmware
===============

### IMPORTANT: Versioning:
Each of the repositories in the following table has a version number
composed of 3 numbers in the form: **v x.y.z**

|  Tools  [T]    |  Libraries [L] |  Firmware [F]            |
|-----------------|---------------|--------------------------|
| qbmove simulink | qbAPI         | qbmove firmware          |
| qbmoveadmin     |               | qbmove advanced firmware |
| handmoveadmin   |               | hand firmware micro      |

E.g. **xT** is the **x** number of the Tools whereas **yF** is the **y** number of the Firmware version.

- Every change in the number **z** means a change in the respective repo which not implies changes in other repos.
- Every change in the number **y** in a repo is backward compatible reading the table from right to left. This means that
if you have some new feature in a Firmware, you can still use old Libraries and Tools for management, but of course
you will not be able to use the new features. In this case the rule is **yF >= yL >= yT**.
- Every change in the number **x** means a change which is not backward compatible, hence you will need to update
everything to use it. In this case the rule is **xF = xL = xT**.

Summarising
- **z** independent
- **yF >= yL >= yT**
- **xF = xL = xT**

E.g.

| Tools              | Libraries    | Firmware               | Compatible |
|--------------------|--------------|------------------------|------------|
| qbmoveadmin v4.2.3 | qbAPI v4.5.0 | qbmove firmware v4.6.7 | YES        |
| qbmoveadmin v3.2.3 | qbAPI v4.5.0 | qbmove firmware v4.6.7 | NO         |
| qbmoveadmin v4.2.3 | qbAPI v4.5.7 | qbmove firmware v4.5.0 | YES        |

Firmware for qbmove for *qbcontrol_beta4.2* board

Just open it with PSoC Creator and upload it onto the board
