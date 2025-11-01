# 시스템 폰트 및 테마 사용 설정

이 앱은 Flatpak 샌드박스 보안을 위해 기본적으로 시스템 폰트와 테마에 직접 접근하지 못합니다.

한글 폰트와 시스템 테마를 사용하려면 아래 방법 중 하나를 선택하세요.

## 방법 1: Flatseal 사용 (추천)

1. Flatseal 설치:
```bash
flatpak install flathub com.github.tchx84.Flatseal
```

2. Flatseal 실행 후 "ummide" 앱 선택

3. 다음 권한 추가:
   - **Filesystem** 섹션:
     - `xdg-config/fontconfig` (Other files) - 읽기 전용
     - `xdg-config/gtk-3.0` - 읽기 전용
     - `xdg-config/gtk-4.0` - 읽기 전용  
     - `~/.cache/fontconfig` - 읽기 전용
   
   - **Environment** 섹션:
     - `LANG=ko_KR.UTF-8` 추가

4. 앱 재시작

## 방법 2: 터미널 명령어 사용

```bash
# 한글 폰트 설정 접근
flatpak override --user --filesystem=xdg-config/fontconfig:ro net.bloupla.ummide
flatpak override --user --filesystem=~/.cache/fontconfig:ro net.bloupla.ummide

# GTK 테마 설정 접근  
flatpak override --user --filesystem=xdg-config/gtk-3.0:ro net.bloupla.ummide
flatpak override --user --filesystem=xdg-config/gtk-4.0:ro net.bloupla.ummide

# 한글 로케일 설정
flatpak override --user --env=LANG=ko_KR.UTF-8 net.bloupla.ummide
```

## 문제 해결

### 한글 폰트가 여전히 깨지는 경우

1. 시스템에 한글 폰트가 설치되어 있는지 확인:
```bash
fc-list :lang=ko
```

2. 폰트가 없다면 설치:
```bash
# Ubuntu/Debian
sudo apt install fonts-noto-cjk

# Fedora
sudo dnf install google-noto-cjk-fonts

# Arch
sudo pacman -S noto-fonts-cjk
```

3. 폰트 캐시 갱신:
```bash
fc-cache -fv
```

### GTK 테마가 적용되지 않는 경우

1. 시스템 테마 확인:
```bash
gsettings get org.gnome.desktop.interface gtk-theme
```

2. xdg-desktop-portal 실행 확인:
```bash
systemctl --user status xdg-desktop-portal
```

3. 필요한 패키지 설치:
```bash
# Ubuntu/Debian
sudo apt install xdg-desktop-portal-gtk gsettings-desktop-schemas

# Fedora  
sudo dnf install xdg-desktop-portal-gtk gsettings-desktop-schemas
```

## 설정 초기화

모든 override 제거:
```bash
flatpak override --user --reset net.bloupla.ummide
```
