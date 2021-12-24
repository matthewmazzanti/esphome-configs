set -e

for filename in *.yaml; do
    [ -e "$filename" ] || continue
    ! [ "$filename" = "esp.template.yaml" ] || continue
    esphome compile "$filename"
done

for filename in *.yaml; do
    [ -e "$filename" ] || continue
    ! [ "$filename" = "esp.template.yaml" ] || continue
    esphome upload "$filename"
done
