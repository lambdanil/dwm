import subprocess
import time
import os

statuslen = int(125)
# 22
#intray = ["lutris","vlc","steam","discord"]
intray = []

icon_width=3

# do not question how this works, I don't know

def get_date():
    date = subprocess.check_output('date +"%d/%m/%Y | %H:%M"', shell=True)
    date = str(date).replace("b'","")
    date = str(date).replace("\\n'","")
    return(date)
def get_ip():
    interface = str(subprocess.check_output('ip link | grep "state UP"', shell=True))
    if interface == "":
        ip_str = "no connection"
    else:
        interface_split = interface.split(":")
        interface = interface_split[1]
        interface = interface.replace(" ","")
        ip = str(subprocess.check_output(f"ip -br addr show | grep {interface}", shell=True))
        ip_split = ip.split("UP")
        ip = ip_split[1]
        ip = ip.replace(" ","")
        ip_split = ip.split("/")
        ip = ip_split[0]
        ip_str = str(f"{interface}: {ip}")
    return(ip_str)
def get_volume():
    volume = str(subprocess.check_output("pamixer --get-volume", shell=True))
    try:
        mutestr = str(subprocess.check_output("pamixer --get-mute", shell=True))
        mute = "[off]"
    except:
        mute = "[on]"
    volume = volume+"%"
    volume = volume.replace("\\n'","")
    volume = volume.replace("b'","")
    if mute != "[off]":
        return("["+volume+"] "+mute)
    else:
        return(mute)
def get_volume_mic():
    try:
        volume = str(subprocess.check_output("pamixer --default-source --get-mute", shell=True))
        mute = "[off]"
    except:
        mute = "[on]"
    return(mute)
def get_music(symbols,iplen,trayicons,icon_width):
    l1 = 20
    l2 = 15
    try:
        player = str(subprocess.check_output("playerctl -l | head -n 1", shell=True,encoding="utf-8"))
        player_split = player.split(".")
        player = player_split[0]
        titlestr = "title"
        try:
            artist = str(subprocess.check_output(f"(playerctl -a metadata | grep {player}) | grep artist", shell=True,encoding="utf-8"))
        except:
            artist = str(f"xesam:artist              {player}")
        try:
            title = str(subprocess.check_output(f"(playerctl -a metadata | grep {player}) | grep title", shell=True,encoding="utf-8"))
        except:
            try:
                title = str(subprocess.check_output(f"(playerctl -a metadata | grep {player}) | grep 'xesam:url'", shell=True,encoding="utf-8"))
                title = title.replace("file://","")
                title = title.replace("/home/jan","~")
                titlestr = "xesam:url"
            except:
                title = ""
        music=str(title+";;;"+artist)
        music_split = music.split(" ")
#        if len(music_split) == 3:
        try:
            music_split = music.split(";;;")
            title = music_split[0]
            title_split = title.split(titlestr)
            title = title_split[1]
            artist = music_split[1]
            artist_split = artist.split("artist")
            artist = artist_split[1]
            artist = artist.lstrip()
            title = title.lstrip()
#        else:
        except:
            music_split = music.split(";;;")
            title = music_split[0]
            title_split = title.split(titlestr)
            title = title_split[1]
        title = title.lstrip()
        status = str(subprocess.check_output("playerctl status", shell=True))
        title = title.strip()
        artist = artist.strip()
        num = statuslen-102
        maxlen = 50+num
        maxlen_title = 47+num-trayicons
        maxlen_artist = int(12+(num/2))
        l1 = 20 # 20/12
        l2 = 15 # 15/7
#        maxlen_title2 = int(28+(num/2))
        maxlen_title2 = int(((statuslen/2)-len(artist)+1)-(trayicons))
        title_old = title
        artist_old = artist
        if symbols > ((statuslen-70-num)-(trayicons*icon_width)):
            if len(title) > maxlen:
                title = title[:maxlen_title]+"..."
            if (len(artist)+len(title)) > maxlen:
                if len(artist) > maxlen_artist:
                    artist = artist[:maxlen_artist]+"..."
                if len(title) > maxlen_title2:
                    title = title[:maxlen_title2]+"..."
        if (len(artist)+len(title)+(icon_width*2)+symbols+((trayicons*icon_width)-1)) > statuslen-l1:
            if symbols > ((statuslen-70-num-1)-(trayicons*icon_width)):
                if (int((icon_width*trayicons)/2) == (float((icon_width*trayicons)/2))):
                    odd = False
                else:
                    odd = True
                if len(title_old) > (maxlen-((icon_width)*trayicons)):
                    if odd:
                        title = title_old[:maxlen_title-((int((icon_width*trayicons)/2))-1)]+"..."
                    else:
                        title = title_old[:maxlen_title-(int((icon_width*trayicons)/2))]+"..."
                if (len(artist_old)+len(title))+2 > (maxlen-((icon_width)*trayicons)-1):
                    if len(artist) > (maxlen_artist-(int((icon_width/2)*trayicons))):
                        artist = artist[:(maxlen_artist-int(((icon_width/2)*trayicons)))]+"..."
                    if len(title) > (maxlen_title2-icon_width):
                        if odd:
                            title = title_old[:maxlen_title2-((int((icon_width*trayicons)/2))-1)]+"..."
                        else:
                            title = title_old[:maxlen_title2-(int((icon_width*trayicons)/2))]+"..."
        if "Playing" in status:
            if artist != "":
                playing_str = str(f" {artist} :: {title}")
            else:
                playing_str = str(f" {title}")
        else:
            if artist != "":
                playing_str = str(f" {artist} :: {title}")
            else:
                playing_str = str(f" {title}")
    except: 
        playing_str = ("")
#   102=83,88   
    show_ip = False
    if trayicons == 0:
        symbols += 1
    while (len(playing_str)+symbols+iplen+((trayicons*icon_width)-1)) < (statuslen-l1):
        playing_str += " "
        show_ip = True
    while (len(playing_str)+symbols+((trayicons*icon_width)-1)) < (statuslen-l2) and (show_ip == False):
        playing_str += " "
    return(playing_str,show_ip)

while True:
    trayicons=0
    for item in intray:
        try:
            output = subprocess.check_output(f"ps -AF | grep -i {item} | grep -v grep", shell=True)
        except:
            output=""
        if output != "":
            trayicons+=1
    status_ip = get_ip()
    status_date = get_date()
    status_volume = get_volume()
    status_mic = get_volume_mic()
    status_music,ipshow = get_music(len(status_date)+len(status_volume)+len(status_mic),len(status_ip),trayicons,icon_width)
    space = ""
    if trayicons == 0:
#        space = " "
        space = ""
    else:
        space = ""
    if ipshow == False:
        status = str(f"{status_music} |  {status_volume}  {status_mic} |  {status_date}{space}")
#        status = str(f"{status_music} | {status_volume} | {status_mic} | {status_date}{space}")
    else:
        status = str(f"{status_music} |  {status_ip} |  {status_volume}  {status_mic} |  {status_date}{space}")
#        status = str(f"{status_music} | {status_ip} | {status_volume} | {status_mic} | {status_date}{space}")
    if '"' in status:
        status = status.replace('"',"'")
    os.system(f'xsetroot -name "                                                                                            {status}"')
#    print(status)
    time.sleep(1)
