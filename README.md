# AICOM-DT

## Quick Start

1. Clone Repos
2. Install `pipenv`
3. `cd` into AICOM-DT and use `pipenv shell` to launch pipenv shell
4. `cd` into AICOM-DT and use `pipenv install` to install PYTHON dependencies
5. `cd` into frontend and use `npm install`to install JAVASCRIPT dependencies
6. In AICOM-DT use `python manage.py runserver`to start server
7. Run Celery: `celery -A digital_twin worker -l info --pool=solo`
8. Run Celery Monitor: `celery -A digital_twin flower`
9. Run Celery Beat: `celery -A digital_twin beat -l info`
10. To Run Server Locally `py manage.py runserver 0.0.0.0:8000`
11. Access to Website `http://10.42.12.37:8000/home`

## To Fix

1. Only certain length for file name allowed
2. Leave Data Folder in Root Directory

## Infos

To Shut Down Celery Workers: `celery -A digital_twin control shutdown`
