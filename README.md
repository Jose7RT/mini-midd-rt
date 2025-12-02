```sh
sudo apt install clang
clang --version
Ubuntu clang version 18.1.3 (1ubuntu1)

sudo apt install cmake
cmake --version
cmake version 3.28.1

pipx install conan
conan --version
Conan version 2.23.0

sudo apt install nodejs
node --version
v18.19.1

sudo apt install npm
npm --version
9.2.0

docker --version # TODO
```


# Build local (conan + cmake)
```sh
# 1) Crear carpeta build
mkdir -p build/release

# 2) Instalar dependencias con Conan v2
#    Esto generará toolchain, CMakeDeps y scripts de entorno
conan install . --profile=gcc20 --build=missing -of build/release

# 3) Configurar CMake (conan generará la toolchain automáticamente)
cmake --preset conan-release

# 4) Compilar
cmake --build --preset conan-release
```


# Probar el backend localmente
Ejecuta desde mini-middleware/backend/build:
```sh
./build/release/backend
```

Prueba en navegador:
```sh
http://localhost:3000/api/health
```

Prueba en terminal:
```sh
curl -s http://127.0.0.1:3000/api/health | jq
```






# Preparar el frontend minimal para probar con proxy
En mini-middleware/frontend crea una app Angular (si no la tienes ya):
```sh
cd ../../frontend
# instalar angular cli si no lo tienes
npm install -g @angular/cli

# crear una app mínima (elige nombre 'frontend')
ng new frontend --defaults --skip-git
cd frontend
```
Ahora, crea proxy.conf.json dentro de frontend/frontend (ruta de la app) con este contenido:
```json
{
  "/api": {
    "target": "http://localhost:3000",
    "secure": false,
    "changeOrigin": true,
    "logLevel": "debug"
  }
}
```

# Código Angular mínimo para llamar a /api/health
src/app/health.service.ts
```ts
import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({ providedIn: 'root' })
export class HealthService {
  constructor(private http: HttpClient) {}
  getHealth(): Observable<any> {
    return this.http.get('/api/health'); // proxy maneja el reenvío en dev
  }
}
```
Y en app.component.ts:
```ts
import { Component, OnInit } from '@angular/core';
import { HealthService } from './health.service';

@Component({
  selector: 'app-root',
  template: `
    <h1>Mini Middleware - Health</h1>
    <pre *ngIf="status">{{ status | json }}</pre>
    <button (click)="check()">Check health</button>
  `
})
export class AppComponent implements OnInit {
  status: any;
  constructor(private hs: HealthService) {}
  ngOnInit() {}
  check() {
    this.hs.getHealth().subscribe(res => this.status = res, err => this.status = {error: err});
  }
}
```
```sh
ng serve --proxy-config proxy.conf.json
```