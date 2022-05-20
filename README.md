# AFL: ファズがターゲットに渡るまで

前提：forkserverなし

## ディレクトリ構成

- afl-fuzz.c: 疑似[afl-fuzz.c](https://github.com/google/AFL/blob/master/afl-fuzz.c)
- target.c: ファジング対象

## 動作順序

1. afl-fuzz： `.cur_input`に対してファズを書き込む
2. afl-fuzz： `lseek`により、ファイルの読み書き位置を先頭に戻す
   1. 注：lseekがないとターゲットにファズを渡せない
3. afl-fuzz： 子プロセスのファイルディスクリプタ0(標準入力)を、`.cur_input`のファイルディスクリプタで上書きする(`dup2(out_fd, 0)`)
4. afl-fuzz: 子プロセスがターゲットを起動する
5. target: 標準入力から文字を取得する。このとき、ファイルディスクリプタ0は`.cur_input`のファイルディスクリプタで上書きされているため、`.cur_input`の中身を読み込む
6. target: 読み込んだ文字列を`out.txt`に書き込む。

## Usage

```bash
$ ./make
$ ./afl-fuzz
parent process
child process
Hello,World!
child process exit
$ cat ./out.txt
Hello,World!
```
