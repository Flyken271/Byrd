{ stdenv, fetchFromGitHub, vte, libconfig, glib, pkgconfig }:

stdenv.mkDerivation {
  pname = "byrd";
  version = "git-20200312";

  src = fetchFromGitHub {
    owner = "Flyken271";
    repo = "Byrd";
    rev = "b65b677ea504592e4d3b45c32bb75342e03956f5";
    sha256 = "1d575bly2ywgp8nmsddr976i5w3nvh23h8lak2n4m2rjmm3n9wxg";
  };

  nativeBuildInputs = [ pkgconfig ];
  buildInputs = [ vte glib libconfig ];

  buildPhase = ''
    gcc main.c -o byrd $(pkg-config --libs --cflags vte-2.91 libconfig)
  '';

  installPhase = ''
    mkdir -p $out/bin
    install -m 0755 -t $out/bin byrd
  '';
}
