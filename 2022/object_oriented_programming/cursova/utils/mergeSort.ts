type Items = (number | string)[]

export function mergeSort(items: Items): Items {
  return divide(items)
}

function divide(items: Items): Items {
  let halfLength = Math.ceil(items.length / 2)
  let low = items.slice(0, halfLength)
  let high = items.slice(halfLength)

  if (halfLength > 1) {
    low = divide(low)
    high = divide(high)
  }

  return combine(low, high)
}

function combine(low: Items, high: Items): Items {
  let indexLow = 0
  let indexHigh = 0
  let lengthLow = low.length
  let lengthHigh = high.length
  let combined = []

  while (indexLow < lengthLow || indexHigh < lengthHigh) {
    let lowItem = low[indexLow]
    let highItem = high[indexHigh]

    if (lowItem !== undefined) {
      if (highItem === undefined) {
        combined.push(lowItem)
        indexLow++
      } else {
        if (lowItem <= highItem) {
          combined.push(lowItem)
          indexLow++
        } else {
          combined.push(highItem)
          indexHigh++
        }
      }
    } else {
      if (highItem !== undefined) {
        combined.push(highItem)
        indexHigh++
      }
    }
  }

  return combined
}
