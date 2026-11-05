#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
import random
import json

# --- 1. Python 側での動的計算（サーバーサイド処理） ---
stage_data = []
num_obstacles = 50

for i in range(num_obstacles):
    z = -10 - (i * 3.0)
    x_wave = math.sin(i * 0.5) * 4.0
    x_random = random.uniform(-2.0, 2.0)

    stage_data.append({
        "x": round(x_wave + x_random, 2),
        "y": 0.6,
        "z": round(z, 2),
        "speed": round(random.uniform(0.15, 0.35), 2)
    })

json_stage = json.dumps(stage_data)

# --- 2. HTTP ヘッダー出力 ---
print("Content-Type: text/html; charset=utf-8")
print()

# --- 3. レンダリング用の HTML/JS 出力 ---
print(f"""<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">
    <title>CGI Generated 3D Stage</title>
    <style>
        body {{ margin: 0; overflow: hidden; background: #050510; font-family: monospace; }}
        #info {{
            position: absolute; top: 10px; left: 10px; color: #00ffcc;
            background: rgba(0,0,0,0.7); padding: 10px; border-radius: 5px;
            user-select: none;
        }}
        #game-over {{
            display: none;
            position: absolute; top: 50%; left: 50%;
            transform: translate(-50%, -50%);
            color: #ff0055; font-size: 36px; font-weight: bold;
            text-align: center; background: rgba(0, 0, 0, 0.85);
            padding: 30px; border: 2px solid #ff0055; border-radius: 8px;
            user-select: none;
        }}
    </style>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js"></script>
</head>
<body>
    <div id="info">
        [CGI Server] Stage Generated: {len(stage_data)} obstacles<br>
        Move: WASD / Arrow Keys
    </div>

    <div id="game-over">
        GAME OVER<br>
        <span style="font-size: 18px; color: #fff;">F5 (or Reload) to generate a new Python stage!</span>
    </div>

    <script>
        const stageData = {json_stage};

        const scene = new THREE.Scene();
        scene.fog = new THREE.FogExp2(0x050510, 0.03);

        const camera = new THREE.PerspectiveCamera(60, window.innerWidth / window.innerHeight, 0.1, 1000);
        camera.position.set(0, 4, 8);

        const renderer = new THREE.WebGLRenderer({{ antialias: true }});
        renderer.setSize(window.innerWidth, window.innerHeight);
        document.body.appendChild(renderer.domElement);

        const light = new THREE.PointLight(0x00ffff, 2, 50);
        light.position.set(0, 5, 0);
        scene.add(light);
        scene.add(new THREE.AmbientLight(0x222244));

        // プレイヤー (自機)
        const player = new THREE.Mesh(
            new THREE.ConeGeometry(0.5, 1.5, 4),
            new THREE.MeshBasicMaterial({{ color: 0x00ffcc, wireframe: true }})
        );
        player.rotation.x = Math.PI / 2;
        player.position.y = 0.5;
        scene.add(player);

        // 障害物群
        const obstacles = [];
        stageData.forEach(data => {{
            const mesh = new THREE.Mesh(
                new THREE.BoxGeometry(0.8, 0.8, 0.8),
                new THREE.MeshBasicMaterial({{ color: 0xff0055, wireframe: true }})
            );
            mesh.position.set(data.x, data.y, data.z);
            mesh.userData = {{ speed: data.speed }};
            scene.add(mesh);
            obstacles.push(mesh);
        }});

        const keys = {{}};
        window.addEventListener('keydown', e => keys[e.key] = true);
        window.addEventListener('keyup', e => keys[e.key] = false);

        let isGameOver = false;

        function animate() {{
            if (isGameOver) return; // ゲームオーバー時はループ停止

            requestAnimationFrame(animate);

            // 自機移動
            if ((keys['ArrowLeft'] || keys['a']) && player.position.x > -6) player.position.x -= 0.15;
            if ((keys['ArrowRight'] || keys['d']) && player.position.x < 6) player.position.x += 0.15;

            // 障害物更新 & 衝突判定
            obstacles.forEach(obs => {{
                obs.position.z += obs.userData.speed;
                obs.rotation.x += 0.02;
                obs.rotation.y += 0.02;

                // 衝突判定 (自機と障害物の3D距離判定)
                const dist = player.position.distanceTo(obs.position);
                if (dist < 0.8) {{
                    isGameOver = true;
                    document.getElementById('game-over').style.display = 'block';
                }}

                // 通り過ぎたら奥に再配置
                if (obs.position.z > 10) {{
                    obs.position.z = -120;
                }}
            }});

            renderer.render(scene, camera);
        }}
        animate();
    </script>
</body>
</html>
""")
