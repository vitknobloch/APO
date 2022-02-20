#!/bin/sh

eval "$(ssh-agent)"
ssh-add ~/.ssh/mzapo-root-key
ssh-add ~/.ssh/postel_fel

return 0