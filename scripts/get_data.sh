# Fetch the callsign country tables from CQRLog, and parse them into
#  c code. This script should be run from the top-level directory
#  of this program's source
#!/usr/bin/bash
mkdir -p tmp
curl -o tmp/area.tbl https://raw.githubusercontent.com/ok2cqr/cqrlog/v2.3.0/ctyfiles/AreaOK1RR.tbl 
curl -o tmp/country.tbl https://raw.githubusercontent.com/ok2cqr/cqrlog/v2.3.0/ctyfiles/Country.tab 
./scripts/parse_areas.pl

