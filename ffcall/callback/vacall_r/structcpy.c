/* copy structs */

/*
 * Copyright 1995-1999 Bruno Haible, <bruno@clisp.org>
 *
 * This is free software distributed under the GNU General Public Licence
 * described in the file COPYING. Contact the author if you don't have this
 * or can't live with it. There is ABSOLUTELY NO WARRANTY, explicit or implied,
 * on this software.
 */

#if defined(__STDC__) || defined(__GNUC__) || defined(__cplusplus)
void __structcpy (void* dest, void* src, unsigned long size, unsigned long alignment)
#else
void __structcpy(dest,src,size,alignment)
  void* dest;
  void* src;
  unsigned long size;
  unsigned long alignment;
#endif
{
  if (alignment % sizeof(long))
    { char* d = (char*)dest;
      char* s = (char*)src;
      do { *d++ = *s++; } while (--size > 0);
    }
  else
    /* If the alignment is a multiple of sizeof(long), the size is as well. */
    { long* d = (long*)dest;
      long* s = (long*)src;
      do { *d++ = *s++; } while ((size -= sizeof(long)) > 0);
    }
}
