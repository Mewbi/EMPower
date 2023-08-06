FROM python:3.9.17-slim

WORKDIR /app

# Copy source code to workdir
COPY . /app

# Install as dependences
RUN pip install --no-cache-dir websockets asyncio pyserial

# Init program
CMD ["python3", "main.py"]