# Making a board

# 1 - copy the template file
cp esp.template.yaml <name of the template>.yaml

# 2 - rename the class in the file
  name: null 

# Flashing a board
`esphome run --device=/dev/cu.wchusbserial1410 <name of the template>.yaml`

# Add to Home Assistant
- Configuration > Integrations
- Click [+ Add Integration]
- Select [ESP Home]
- For host, put in the host name from step 2