# Smart Pool Projekt: OpenHAB

## Raspberry

https://docs.openhab.org/installation/openhabian.html#manual-setup

``` 
sudo openhabian-config 
```

## Backup

TODO https://www.linux-tips-and-tricks.de/de/schnellstart-rbk

## Konfiguration

### File Locations Repository Installation	

* openHAB application	`/usr/share/openhab2`	
* Additional add-on files	`/usr/share/openhab2/addons`	
* Site configuration	`/etc/openhab2`	
* Log files	`/var/log/openhab2`	
* Userdata like rrd4j databases	`/var/lib/openhab2`	
* Backups folder	`/var/lib/openhab2/backups`	
* Service configuration	`/etc/default/openhab2`

Quelle: http://docs.openhab.org/installation/linux.html#file-locations

### Zugriff vom Windows-Computer einrichten

Da nicht jeder auf dieses Verzeichnis zugreifen soll, muss Samba installiert und ein wenig an der Samba Konfiguration für openHAB angepasst werden.

```
sudo apt-get install samba samba-common-bin
```

#### Konfiguration

Die Konfiguration `/etc/samba/smb.conf` muss angepasst werden:

```
[global]
   security = user
```

Und am Ende um folgende Einträge ergänzt werden:

```
[openHAB2-userdata]
  comment=openHAB2 userdata
  path=/var/lib/openhab2
  browseable=Yes
  writeable=Yes
  only guest=no
  public=no
  create mask=0777
  directory mask=0777

[openHAB2-conf]
  comment=openHAB2 site configuration
  path=/etc/openhab2
  browseable=Yes
  writeable=Yes
  only guest=no
  public=no
  create mask=0777
  directory mask=0777

[openHAB2-app]
  comment=openHAB2 application
  path=/usr/share/openhab2
  browseable=Yes
  writeable=Yes
  only guest=no
  public=no
  create mask=0777
  directory mask=0777

[openHAB2-logs]
  comment=openHAB2 Logs
  path=/var/log/openhab2
  browseable=Yes
  writeable=Yes
  only guest=no
  public=no
  create mask=0777
  directory mask=0777
```

Sollten schon Freigabe eingerichtet sein, so sollte man ihre Funktion unbedingt prüfen, da 
sich die Globale Option „security“ geändert hat. An „Public“ Freigaben sollte sich aber nichts geändert haben.

Zusätzlich muss ein Samba-User eingerichtet werden. Mit diesem muss man sich an der Freigabe anmelden.

```
smbpasswd -a openhab
```

Mein Benutzer heißt „openhab“, er sollte aber nicht mit dem Linux Benutzer verwechselt werden. Beide bekommen unterschiedliche Passwörter. Wer möchte, kann seinen Benutzer auch anders nennen. Nach einem Restart vom Samba-Dienst kann man die Freigabe testen.

```
service samba restart
```

Sollte es nicht möglich sein Dateien in dem Verzeichnis anzulegen, so muss die Dateisystem- Berechtigung überprüft werden.

```
sudo chown -hR openhab:openhab /etc/openhab2 /opt/openhab2/conf
```

Nun kann von Windows aus mit dem Benutzer ```openhab``` auf die Daten zugegriffen werden.

Quellen:

- https://docs.openhab.org/installation/linux.html#network-sharing
- https://www.computer-kern.de/samba-freigabe-fuer-konfigurationsdateien-von-openhab/


#### Datenbank RRD4J

ACHTUNG der ```*``` in der ```rrd4j.persist``` ist kein Platzhalter, sondern zeigt an, dass die Elemente in der Gruppe gespeichert werden sollen!

#### Datenbank Influxdb + Grafana

- https://community.openhab.org/t/influxdb-grafana-persistence-and-graphing/13761/84

- Raspberry: https://community.openhab.org/t/influxdb-grafana-persistence-and-graphing/13761/85

grafana: admin/admin
influxdb: admin/admin, openhab/habopen


#### MQTT

- Mosquitto auf Raspberry installieren:

  ``` 
  sudo apt-get update
  sudo apt-get upgrade
  sudo apt-get install mosquitto
  ```

- 'MQTT Binding' in Paper UI als Add-on unter "Bindings" installieren.

- Konfiguration `services/mqtt.cfg` anpassen.


### Cloud-Zugriff

Es muss das aktuelle JDK installiert sein!
