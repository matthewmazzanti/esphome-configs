{
  inputs = {
    esphome-src = {
      url = "git+file:///home/mmazzanti/src/contrib/esphome?ref=remote_values";
      flake = false;
    };
  };

  outputs = { nixpkgs, esphome-src, ... }: let 
    pkgs = nixpkgs.legacyPackages.x86_64-linux;
  in {
    devShell.x86_64-linux = (pkgs.mkShell {
      buildInputs = with pkgs; [
        (esphome.overridePythonAttrs (attrs: {
          version = builtins.toString esphome-src.lastModified;
          src = esphome-src;
          patches = [];
        }))
        platformio
        pipenv
      ];
    });
  };
}
