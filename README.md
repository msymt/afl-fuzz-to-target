# AFLにおいてファズがターゲットに渡るまで

前提：forkserverなし

## ディレクトリ構成

- afl-fuzz.c: 疑似afl-fuzz.c
- target.c: ファジング対象

## 動作過程

1. afl-fuzzが`.cur_input`に対してファズを書き込む。
2. `lseek`により、ファイルの読み書き位置を先頭に戻す。
   1. 注：lseekがないとターゲットにファズを渡せない。
3. `afl-fuzz`が、子プロセスの標準入力のファイルディスクリプタを、`.cur_input`のファイルディスクリプタで上書きする(`dup2(out_fd, 0)`)。
4. 子プロセスがターゲットを起動する。
5. 子プロセスが標準入力から文字を取得する。このとき、標準入力のファイルディスクリプタは`.cur_input`のファイルディスクリプタで上書きされているため、`.cur_input`の中身を読み込む。
6. 読み込んだ文字列を`out.txt`に書き込む。

## ややこしい点

`.cur_input`の中身を子プロセス（ターゲット）に渡すために、`dup2()`を使用。

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
