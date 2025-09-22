# Resumen del Problema de la Permutación Bitónica

El problema nos pide completar una permutación con elementos faltantes para que forme una secuencia bitónica (primero estrictamente creciente, luego estrictamente decreciente), o determinar si no es posible. La solución se basa en una aproximación codiciosa y recursiva, fundamentada en dos lemas clave.

## Lemas Fundamentales

- **El número 1 debe estar en un extremo:**  
  En cualquier permutación de montaña de 1 a N, el número 1 debe estar en uno de los dos extremos. Esto se debe a que es el número más pequeño y no puede haber una secuencia decreciente antes de él ni una creciente después de él.

- **Naturaleza Recursiva:**  
  Si eliminamos el 1 de la permutación de montaña y decrementamos todos los demás números en 1, el resultado es una permutación de montaña válida de tamaño N-1. Este principio nos permite reducir el problema de forma iterativa.

## Algoritmo de la Solución

El algoritmo procesa la secuencia de forma codiciosa, trabajando con los números del 1 al N y una "ventana" de la secuencia que se va reduciendo desde los extremos.

1. **Inicialización:**  
   Se comienza con una ventana que abarca toda la secuencia. Se pre-calculan los números faltantes.

2. **Iteración:**  
   Para cada número n de 1 a N, se evalúan las siguientes condiciones:

   - **Si n ya está en la secuencia:**  
     Debe estar obligatoriamente en uno de los extremos de la ventana (`l` o `r`). Si no es así, no hay solución. Si está en un extremo, se reduce la ventana.

   - **Si n falta:**  
     Se debe colocar en un extremo vacío de la ventana (`l` o `r`).
     - Un solo extremo vacío: Se coloca n ahí y se reduce la ventana.
     - Ambos extremos vacíos: Este es el caso más complejo. La decisión se toma para "priorizar el lado más restringido".
       - Se buscan los números no-cero más cercanos a los extremos de la ventana, `x` (desde `l`) e `y` (desde `r`).
       - Si `x < y`, se elige el extremo izquierdo (`l`) para colocar n. La lógica es que la sección `l...dx` debe ser creciente, y hay menos números disponibles para hacerlo.
       - Si `y < x`, se elige el extremo derecho (`r`).
       - Si `x = y`, se elige el lado con menos ceros para llenar. Esto ayuda a evitar "picos" no válidos al priorizar la sección más corta.

3. **Resultado:**  
   Si el proceso se completa para todos los números, se imprime la secuencia resultante. Si en algún momento una condición de fallo se cumple, se imprime un `*`.

## Implementación

La implementación en C++ utiliza iteradores para simular la ventana deslizante (`l` y `r`). El uso de `std::find_if` y `std::distance` simplifica la lógica de encontrar los elementos no-cero y determinar la longitud de las secciones.

- El código utiliza un `std::set` (`s`) para mantener un registro de los números faltantes, lo que permite una verificación rápida (`s.count(nval)`).
- La lógica de las etiquetas `goto` (`fallo` y `desempate`) podría ser refactorizada usando estructuras de control más convencionales, pero es funcional y refleja el flujo del algoritmo.

Este enfoque codicioso garantiza que si existe una solución, el algoritmo la encontrará. La prueba se basa en un argumento de intercambio que demuestra que cualquier solución donde se toma una decisión "no óptima" puede ser transformada en una solución "óptima" sin invalidar la permutación de montaña.
