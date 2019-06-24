# タイトル(GameTitle)
STEALSMISSONS

# 制作期間
5カ月

# 開発環境(Development Tools)
+ Visual Studio 2010 community
+ DirectX9
+ Metasequoia
+ Studio One3


# 開発言語(Programming Language)
+ C++

# 操作方法(Operate)
+ 移動(Move):W A S D

+ 決定(Enter):Enter Key

+ アイテム使用(Use Item): i



# 敵のAI
デザインパターンの「 State 」を使用する事で敵の行動パターンを自由にプログラム内で組み替えられるようになりました。


![](data\ScreenShot/ScreenShot5.jpg)


敵のステートパターンをコンソールで
出力させ、デバッグがしやすいように
しました。


![](data\ScreenShot/ScreenShot6.jpg)

![](data\ScreenShot/ScreenShot2.jpg)

![](data\ScreenShot/ScreenShot3.jpg)


# 敵の巡回経路プログラム
移動する場所に外部ファイルで設定した制御点を置き
制御点に向かって補間して移動します。

![](data\ScreenShot/ScreenShot7.jpg)


# 敵の視界判定
外積と内積を使用し、一定範囲内かつ一定距離内に
入ったら敵に発見されます。

![](data\ScreenShot/ScreenShot4.jpg)