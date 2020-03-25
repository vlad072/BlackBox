# BlackBox Project
This software is distributed under the GNU GPL license https://www.gnu.org/licenses/gpl.txt

©2019 Pervuninsky Vlad http://drive2.ru/users/vlad0722/

mail to: pervuninsky.vlad@gmail.com

### Usage 
DTMF key:
|    Key     |          Descript                 |
|------------ | -------------|
 |2 | keep connection enable/disable. reconnect when connection loss
 |3 | shock sensor enable/disable
 |5 | dvr power turn on/off
 |# | restore modem defaults then reboot (BLUETOOTH PIN WILL BE RESETING TO DEFAULT!!!)
 |* | setup mode

Initial settings through BT SPP:
| Command | Descript |
|------------ | -------------|
| srv=url,port |   mqtt broker addr & port |
| usr=username |   broker login |
| pwd=password |   broker password |
| sens=0 |         teach the internal pcb temperature sensor (must be defined first! all ext sensors disconnected!) |
| sens=1 |         -/- engine (his one connected only!) |
| sens=2 |         -/- outside air (his one connected only!) |
| sens=3 |         -/- vehicle (his one connected only!) |
| sens=? |         read sensors info |
| btpin=xxxx |     update bt pin & detach all paired devs |
| ? |              help |

### Tech info

##### MQTT topics:

Root topics:
* 'cmd/#'    - commands from user to car (below remark 'c')
* 'inf/#'    - feedback from car to user app (below 'i')
* 'notify'   - push notification to user
* 'log'      - evnt log

Sub topics:
* btpwr'    - on/off bt power                        (c/i)
* 'btcon'    - number conn/paired devs via bt hsp     (i)
* 'sq'       - baseband signal level                  (i)
* 'warmup'   - remote warmup engine                   (i)
* 'wutm'     - warmup timer in min's                  (c/i)
* 'wutp'     - warmup temperature limit               (c/i)
* 'engtp'    - current engine temper                  (i)
* 'pcbtp'    - current pcb temper                     (i)
* 'outtp'    - outside temper                         (i)
* 'balance'  - sim-card balance                       (i)
* 'place'    - lbs location <nn.nnnn,ee.eeee>         (i)
* 'lock'     - lock/ulock doors                       (c/i)
* 'siren'    - siren act/silent mode                  (c/i)
* 'shock'    - chock sensor en/dis                    (c/i)
* 'sms'      - sms/push notify                        (c/i)
* 'alarm'    - alarms byte/reset                      (c/i)
* 'vbatt'    - battery voltage                        (i)
* 'engr'     - engine running                         (i)
* 'drop'     - door opened                            (i)
* 'hdop'     - hood opened                            (i)
* 'start'    - remote start/stop engine               (c)
* 'upd'      - update info panel                      (c)
* 'online'   - blackbox connected                     (i)
* 'dvr'      - dvr on/off                             (c/i)
* 'gear'     - gear state N/D                         (i)

##### Voice *.amr files into modem:

* 'recov'    - modem recovery
* 'keep'     - keep connect
* 'nkeep'    - don't keep
* 'shken'    - shock sensor enabled
* 'shkdis'   - ...disabled
* 'dvron'    - dvr power on
* 'dvroff'   - ..off
* 'setup'    - initial setup mode
* 'error'    - error
* 'hello'    - hello :)
* 'fire'     - fire detected
* 'ignon'    - ignition turn-on
* 'dooropen' - door openend
* 'hoodopen' - hood or trunk opened
* 'shock'    - 2nd lvl bang alarm
