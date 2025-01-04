{pkgs ? import <nixpkgs> {}}:
with pkgs;
  mkShell {
    nativeBuildInputs = [gcc];
    buildInputs = [
      (texliveBasic.withPackages (ps:
        with ps; [
          latexmk
          amsmath
          amsfonts
          algorithms
          float
          etoolbox
        ]))
    ];
  }
